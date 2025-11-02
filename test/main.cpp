#pragma once
#include <Windows.h>
#include <print>

#include <api/imports.hpp>
#include <../src/runtime.hpp>

#include <event/events.hpp>
#include <api/helpers/mcuirc.hpp>
#include <api/mc/client/renderer/MeshHelpers.hpp>

BOOL APIENTRY DllMain(HINSTANCE, DWORD, LPVOID) {
    return TRUE;
}

void after_ui(selaura::SetupAndRenderEvent<selaura::event_phase::post>& ev) {
    auto scrn = ev.mCtx->mScreenContext;
    scrn->tessellator->begin(mce::PrimitiveMode::QuadList, 8);
    scrn->tessellator->color(0.f, 0.f, 1.f, 1.f);

    //ev.mCtx->mClientInstance->mGuiData->displayLocalMessage("this is from a plugin!");
}

SELAURA_API void SelauraPluginInit(selaura::runtime* runtime) {
    runtime->event_manager->subscribe(&after_ui);
}