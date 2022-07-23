#include "imtui/imtui.h"

#include "imtui/imtui-impl-ncurses.h"

int main() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    auto screen = ImTui_ImplNcurses_Init(true);
    ImTui_ImplText_Init();

    int nframes = 0;
    float fval = 1.23f;

    bool isRunning = true;

    while (isRunning) {
        ImTui_ImplNcurses_NewFrame();
        ImTui_ImplText_NewFrame();

        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(4, 2), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(50.0, 10.0), ImGuiCond_Once);
        ImGui::Begin("ImTui App Template");
        ImGui::Text("%s", "");
        ImGui::Text("NFrames = %d", nframes++);
        ImGui::Text("Mouse Pos : x = %g, y = %g", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
        ImGui::Text("Time per frame %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Float:");
        ImGui::SameLine();
        ImGui::SliderFloat("##float", &fval, 0.0f, 10.0f);

        ImGui::Text("%s", "");
        if (ImGui::Button("Exit program", { ImGui::GetContentRegionAvail().x, 2 })) {
            isRunning = false;
        }

        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape))) {
            isRunning = false;
        }

        ImGui::End();

        ImGui::Render();

        ImTui_ImplText_RenderDrawData(ImGui::GetDrawData(), screen);
        ImTui_ImplNcurses_DrawScreen();
    }

    ImTui_ImplText_Shutdown();
    ImTui_ImplNcurses_Shutdown();

    return 0;
}
