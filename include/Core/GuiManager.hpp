#pragma once
#include <SFML/Graphics.hpp>
#include "imgui.h"

#include "RenderContext.hpp"

class GuiManager {
public:
	static void render(const RenderContext& ctx);

private:
	static void renderControlPanel(const RenderContext& ctx);

	static void renderSpeedReset(const RenderContext& ctx, int targetInd);

	///

	static void renderInfo(const RenderContext& ctx);

	static void renderTypeInfo(const RenderContext& ctx, int targetInd);
	static void renderNameInfo(const RenderContext& ct, int targetIndx);
	static void renderMassInfo(const RenderContext& ctx, int targetInd);
	static void renderDistanceFromSunInfo(const RenderContext& ctx, int targetInd, int starInd);
	static void renderVelocityInfo(const RenderContext& ctx, int targetInd);
};