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

void after_ui(Selaura::SetupAndRenderEvent<Selaura::EventPhase::Post>& ev) {
    auto scrn = ev.mCtx->mScreenContext;
    scrn->tessellator->begin(mce::PrimitiveMode::QuadList, 4);
    scrn->tessellator->color(1.f, 1.f, 1.f, 1.f);

    glm::vec2 pos = {0, 0};
    glm::vec2 size = {100, 100};

    scrn->tessellator->vertex(pos.x, pos.y + size.y, 0.f);
    scrn->tessellator->vertex(pos.x + size.x, pos.y + size.y, 0.f);
    scrn->tessellator->vertex(pos.x + size.x, pos.y, 0.f);
    scrn->tessellator->vertex(pos.x, pos.y, 0.f);

    auto mat = mce::MaterialPtr::createMaterial(HashedString("ui_fill_color"));
    char pad[0x58]{};
    MeshHelpers::renderMeshImmediately(scrn, scrn->tessellator, mat, pad);


    //ev.mCtx->mClientInstance->mGuiData->displayLocalMessage("this is from a plugin!");
}

SELAURA_API void SelauraPluginInit(Selaura::Runtime* pRuntime) {
    pRuntime->mEventManager->subscribe(&after_ui);
}