#pragma once
#include <Windows.h>
#include <print>

#include <api/imports.hpp>
#include <loader/runtime.hpp>

#include <event/events.hpp>
#include <api/helpers/mcuirc.hpp>

BOOL APIENTRY DllMain(HINSTANCE, DWORD, LPVOID) {
    return TRUE;
}

void before_ui(selaura::BeforeSetupAndRenderEvent& ev) {
    selaura::mcuirc ctx(ev.mCtx);
    ctx.fill_rect({350, 170}, {50, 50}, {255, 0, 0, 1});
    ctx.stroke_rect({350, 250}, {50, 50}, {0, 255, 255, 1}, 10);
}

SELAURA_API void SelauraPluginInit(selaura::runtime* runtime) {
    runtime->event_manager->subscribe(&before_ui);
}