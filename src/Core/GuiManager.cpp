#include "Core/GuiManager.hpp"

#include "Core/Constants.hpp"
#include "Core/Camera.hpp"
#include "Simulation/Space.hpp"
#include "Core/InputState.hpp"

#include "Entities/CelestialBody.hpp"

#include "imgui-SFML.h"

#include <string>


void GuiManager::render(const RenderContext& ctx) {
	ImGui::SetNextWindowSize(ImVec2(Config::Gui::width, Config::Gui::height), ImGuiCond_Always);

	ImVec2 pos = ImVec2(ctx.window.getSize().x, 0.f);
	ImVec2 pivot = ImVec2(1.f, 0.f);
	ImGui::SetNextWindowPos(pos, ImGuiCond_Always, pivot);

    ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;

    ImGui::Begin("ImGui", nullptr, windowFlags);
	ImGui::GetIO().FontGlobalScale = Config::Gui::fontGlobalCase;
	ImGui::StyleColorsClassic;

	renderControlPanel(ctx);
	renderInfo(ctx);

    ImGui::End();
}

///

void GuiManager::renderControlPanel(const RenderContext& ctx) {
	ImGui::SeparatorText("Control Panel");

    renderTimeAcceleration(ctx);

    renderScaleSlider(ctx);

    const int targetInd = ctx.camera.getTargetInd();
    renderSpeedReset(ctx, targetInd);
}



void GuiManager::renderScaleSlider(const RenderContext& ctx) {
    double scale = ctx.camera.getInitScale();

    double minInitScale = Config::Camera::minInitScale;
    double maxInitScale = Config::Camera::maxInitScale;

    ImGui::Text("Scale:");
    ImGui::SameLine();
    ImGui::SliderScalar("##", ImGuiDataType_Double, &scale, static_cast<void*>(&minInitScale), static_cast<void*>(&maxInitScale), "%E");

    ctx.camera.setInitScale(scale);
}

void GuiManager::renderTimeAcceleration(const RenderContext& ctx) {
    ImGui::Text("Time Acceleration");

    int timeAcceleration = static_cast<int>(ctx.space.getTimeAcceleration());

    if (ImGui::Button("-1M")) {
        timeAcceleration = ((timeAcceleration - 1) / 1'000'000) * 1'000'000;
        if (timeAcceleration < static_cast<int>(Config::Coefs::minTimeAcceleraion)) timeAcceleration = static_cast<int>(Config::Coefs::minTimeAcceleraion);
    }
    ImGui::SameLine();
    if (ImGui::Button("+1M")) {
        timeAcceleration = (timeAcceleration / 1'000'000 + 1) * 1'000'000;
        if (timeAcceleration > static_cast<int>(Config::Coefs::maxTimeAcceleraion)) timeAcceleration = static_cast<int>(Config::Coefs::maxTimeAcceleraion);
    }

    ImGui::SameLine();

    std::string description = "x" + std::to_string(timeAcceleration);

    ImGui::Text(description.data());


    ImGui::Text("Elapsed Time:");

    ImGui::SameLine();

    double elapsedSimulationTimeInYear = ctx.space.getElapsedSimulationTime() / (60. * 60. * 24. * 365.);

    ImGui::SameLine();

    ImGui::Text(formatDouble(elapsedSimulationTimeInYear, Unit::Year).data());

    ImGui::SameLine();

    ImGui::Text("years");

    ctx.space.setTimeAcceleration(static_cast<float>(timeAcceleration));
}

void GuiManager::renderSpeedReset(const RenderContext& ctx, int targetInd) {
    if (!ctx.mouseStates.isCbSelected) return;

    ImGui::TextColored(ImVec4(255, 0, 0, 255), "Reset Speed:");
    ImGui::SameLine();
    if (ImGui::Button("R")) {
        ctx.space.getBodies().at(targetInd)->setRealV( {.0, .0} );
    }
}



///

void GuiManager::renderInfo(const RenderContext& ctx) {
    ImGui::SeparatorText("Info");
    if (ctx.mouseStates.isCbSelected) {
        const int targetInd = ctx.camera.getTargetInd();

        renderTypeInfo(ctx, targetInd);
        renderNameInfo(ctx, targetInd);

        ImGui::Separator();

        renderMassInfo(ctx, targetInd);
        
        const CelestialBody* parent = ctx.space.getBodies()[targetInd]->getParent();
        const CelestialBody* targetCb = ctx.space.getBodies()[targetInd].get();
        
        while (parent) {
            renderDistanceFromAnotherCbInfo(ctx, targetCb, parent);
            parent = parent->getParent();
        }

        renderVelocityInfo(ctx, targetInd);
    }
    else {
        ImGui::TextWrapped("Click on a celestial body to get information");
        ImGui::Text("");
    }

    ImGui::TextWrapped("In order to see moons change scale of Solar System");
}

void GuiManager::renderTypeInfo(const RenderContext& ctx, int targetInd) {
    std::string description = "Type:";
    ImGui::Text(description.c_str());
    ImGui::SameLine();

    std::string type = typeid(*ctx.space.getBodies().at(targetInd)).name();
    type = type.substr(6);
    ImGui::Text(type.c_str());  // type of Cb
}

void GuiManager::renderNameInfo(const RenderContext& ctx, int targetInd) {
    std::string description = "Name:";
    ImGui::Text(description.c_str());
    ImGui::SameLine();

    std::string name = ctx.space.getBodies().at(targetInd)->getName();
    ImGui::Text(name.c_str());  // name of Cb
}

void GuiManager::renderMassInfo(const RenderContext& ctx, int targetInd) {
    std::string description = "Mass:";
    ImGui::Text(description.c_str());

    ImGui::SameLine();
    double massInEm = ctx.space.getBodies().at(targetInd)->getMass();
    std::string massInEmStr = formatDouble(massInEm, Unit::Em);
    ImGui::Text(massInEmStr.c_str());  // mass of Cb
    ImGui::SameLine();
    ImGui::Text("Earth masses");
}

void GuiManager::renderDistanceFromAnotherCbInfo(const RenderContext& ctx, const auto& targetCb, const auto& anotherCb) {
    std::string anotherName = anotherCb->getName();

    std::string description = "Distance from the " + anotherName + ":";
    ImGui::Text(description.c_str());

    double distanceInMeters = distanseFromAnotherCb(*(anotherCb), *(targetCb));  // distance, meters
    std::string distanceInMetersStr = "\t" + formatDouble(distanceInMeters, Unit::Meter);
    ImGui::Text(distanceInMetersStr.c_str());
    ImGui::SameLine();
    ImGui::Text("m");

    double distanceInAu = distanceInMeters * Config::Coefs::M_TO_AU;
    std::string distanceInAuStr = "\t" + formatDouble(distanceInAu, Unit::Au);
    ImGui::Text(distanceInAuStr.c_str());
    ImGui::SameLine();
    ImGui::Text("au");
}

void GuiManager::renderVelocityInfo(const RenderContext& ctx, int targetInd) {
    std::string description = "Velocity:";
    ImGui::Text(description.c_str());

    double velocityInMps = ctx.space.getBodies().at(targetInd)->getRealV().length();
    std::string velocityInMpsStr = "\t" + formatDouble(velocityInMps, Unit::Mps);
    ImGui::Text(velocityInMpsStr.c_str());
    ImGui::SameLine();
    ImGui::Text("m/s");

    double velocityInAps = velocityInMps * Config::Coefs::M_TO_AU;
    std::string velocityInApsStr = "\t" + formatDouble(velocityInAps, Unit::Aps);
    ImGui::Text(velocityInApsStr.c_str());
    ImGui::SameLine();
    ImGui::Text("au/s");
}