// dear imgui: Platform Binding

// Implemented features:
//  [X] Platform: Clipboard support.
//  [X] Platform: Gamepad support. Enable with 'io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad'.
//  [x] Platform: Mouse cursor shape and visibility. Disable with 'io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange'. FIXME: 3 cursors types are missing from GLFW.
//  [X] Platform: Keyboard arrays indexed using GLFW_KEY_* codes, e.g. ImGui::IsKeyPressed(GLFW_KEY_SPACE).

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you are new to dear imgui, read examples/README.txt and read the documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

// About GLSL version:
// The 'glsl_version' initialization parameter defaults to "#version 150" if NULL.
// Only override if your GL version doesn't handle this GLSL version. Keep NULL if unsure!

#pragma once

IMGUI_IMPL_API bool     ImGui_ImplInputs_InitForOpenGL();
IMGUI_IMPL_API void     ImGui_ImplInputs_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplInputs_NewFrame();

// InitXXX function with 'install_callbacks=true': install GLFW callbacks. They will call user's previously installed callbacks, if any.
// InitXXX function with 'install_callbacks=false': do not install GLFW callbacks. You will need to call them yourself from your own GLFW callbacks.
IMGUI_IMPL_API void     ImGui_ImplInputs_MouseButtonCallback(int button, int action, int mods);
IMGUI_IMPL_API void     ImGui_ImplInputs_ScrollCallback(double xoffset, double yoffset);
IMGUI_IMPL_API void     ImGui_ImplInputs_KeyCallback(int key, int scancode, int action, int mods);
IMGUI_IMPL_API void     ImGui_ImplInputs_CharCallback(unsigned int c);
