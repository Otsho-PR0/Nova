#include <Editor.hpp>
#include <Input.hpp>

#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>
#include <imgui.h>

Editor::Editor() :
	window("Nova", 1024, 600),
	context(window)
{
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(context.GetDevice(), context.GetContext());

	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_NavEnableKeyboard;
	io.Fonts->AddFontFromFileTTF("res/Roboto-Regular.ttf", 15.0f);

	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowPadding = ImVec2(8, 8);
	style.FramePadding = ImVec2(6, 4);
	style.ItemSpacing = ImVec2(6, 5);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.ColorMarkerSize = 4.0f;
	style.SeparatorTextBorderSize = 2.0f;
	style.IndentSpacing = 20.0f;
	style.ScrollbarSize = 12.0f;
	style.GrabMinSize = 10.0f;
	style.TabBarOverlineSize = 0.0f;
	style.DockingSeparatorSize = 1.0f;

	style.WindowMenuButtonPosition = ImGuiDir::ImGuiDir_None;

	style.WindowRounding = 8.0f;
	style.FrameRounding = 3.0f;
	style.PopupRounding = 6.0f;
	style.ScrollbarRounding = 12.0f;
	style.GrabRounding = 3.0f;
	style.TabRounding = 4.0f;

	style.WindowBorderSize = 1.0f;
	style.FrameBorderSize = 0.0f;
	style.PopupBorderSize = 1.0f;

	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);

	ImVec4* colors = style.Colors;

	const ImVec4 Rosewater = ImVec4(0.96078f, 0.87843f, 0.86275f, 0.85f);
	const ImVec4 Flamingo  = ImVec4(0.94902f, 0.80392f, 0.80392f, 0.85f);
	const ImVec4 Pink      = ImVec4(0.96078f, 0.76078f, 0.90588f, 0.85f);
	const ImVec4 Mauve     = ImVec4(0.79608f, 0.65098f, 0.96863f, 0.85f);
	const ImVec4 Red       = ImVec4(0.95294f, 0.54510f, 0.65882f, 0.85f);
	const ImVec4 Maroon    = ImVec4(0.92157f, 0.62745f, 0.67451f, 0.85f);
	const ImVec4 Peach     = ImVec4(0.98039f, 0.70196f, 0.52941f, 0.85f);
	const ImVec4 Yellow    = ImVec4(0.97647f, 0.88627f, 0.68627f, 0.85f);
	const ImVec4 Green     = ImVec4(0.65098f, 0.89020f, 0.63137f, 0.85f);
	const ImVec4 Teal      = ImVec4(0.58039f, 0.88627f, 0.83529f, 0.85f);
	const ImVec4 Sky       = ImVec4(0.53725f, 0.86275f, 0.92157f, 0.85f);
	const ImVec4 Sapphire  = ImVec4(0.45490f, 0.78039f, 0.92549f, 0.85f);
	const ImVec4 Blue      = ImVec4(0.53725f, 0.70588f, 0.98039f, 0.85f);
	const ImVec4 Lavender  = ImVec4(0.70588f, 0.74510f, 0.99608f, 0.85f);
	const ImVec4 Text      = ImVec4(0.80392f, 0.83922f, 0.95686f, 0.85f);
	const ImVec4 Subtext1  = ImVec4(0.72941f, 0.76078f, 0.87059f, 0.85f);
	const ImVec4 Subtext0  = ImVec4(0.65098f, 0.67843f, 0.78431f, 0.85f);
	const ImVec4 Overlay2  = ImVec4(0.57647f, 0.60000f, 0.69804f, 0.85f);
	const ImVec4 Overlay1  = ImVec4(0.49804f, 0.51765f, 0.61176f, 0.85f);
	const ImVec4 Overlay0  = ImVec4(0.42353f, 0.43922f, 0.52549f, 0.85f);
	const ImVec4 Surface2  = ImVec4(0.34510f, 0.35686f, 0.43922f, 0.85f);
	const ImVec4 Surface1  = ImVec4(0.27059f, 0.27843f, 0.35294f, 0.85f);
	const ImVec4 Surface0  = ImVec4(0.19216f, 0.19608f, 0.26667f, 0.85f);
	const ImVec4 Base      = ImVec4(0.11765f, 0.11765f, 0.18039f, 0.85f);
	const ImVec4 Mantle    = ImVec4(0.09412f, 0.09412f, 0.14510f, 0.85f);
	const ImVec4 Crust     = ImVec4(0.06667f, 0.06667f, 0.10588f, 0.85f);

	colors[ImGuiCol_Text] = Text;
	colors[ImGuiCol_TextDisabled] = Overlay1;
	colors[ImGuiCol_WindowBg] = Base;
	colors[ImGuiCol_ChildBg] = Base;
	colors[ImGuiCol_PopupBg] = Mantle;
	colors[ImGuiCol_Border] = Surface1;
	colors[ImGuiCol_BorderShadow] = Crust;

	colors[ImGuiCol_FrameBg] = Surface0;
	colors[ImGuiCol_FrameBgHovered] = Surface1;
	colors[ImGuiCol_FrameBgActive] = Surface2;

	colors[ImGuiCol_TitleBg] = Mantle;
	colors[ImGuiCol_TitleBgActive] = Mantle;
	colors[ImGuiCol_TitleBgCollapsed] = Crust;

	colors[ImGuiCol_MenuBarBg] = Mantle;
	colors[ImGuiCol_ScrollbarBg] = Crust;
	colors[ImGuiCol_ScrollbarGrab] = Surface2;
	colors[ImGuiCol_ScrollbarGrabHovered] = Overlay0;
	colors[ImGuiCol_ScrollbarGrabActive] = Overlay1;

	colors[ImGuiCol_CheckMark] = Blue;
	colors[ImGuiCol_SliderGrab] = Sapphire;
	colors[ImGuiCol_SliderGrabActive] = Sky;

	colors[ImGuiCol_Button] = Surface0;
	colors[ImGuiCol_ButtonHovered] = Surface1;
	colors[ImGuiCol_ButtonActive] = Surface2;

	colors[ImGuiCol_Header] = Surface0;
	colors[ImGuiCol_HeaderHovered] = Surface1;
	colors[ImGuiCol_HeaderActive] = Surface2;

	colors[ImGuiCol_Separator] = Surface1;
	colors[ImGuiCol_SeparatorHovered] = Mauve;
	colors[ImGuiCol_SeparatorActive] = Mauve;

	colors[ImGuiCol_ResizeGrip] = Surface2;
	colors[ImGuiCol_ResizeGripHovered] = Overlay0;
	colors[ImGuiCol_ResizeGripActive] = Overlay1;

	colors[ImGuiCol_Tab] = Surface0;
	colors[ImGuiCol_TabHovered] = Surface2;
	colors[ImGuiCol_TabActive] = Surface1;
	colors[ImGuiCol_TabUnfocused] = Base;
	colors[ImGuiCol_TabUnfocusedActive] = Surface0;

	colors[ImGuiCol_PlotLines] = Flamingo;
	colors[ImGuiCol_PlotLinesHovered] = Pink;
	colors[ImGuiCol_PlotHistogram] = Mauve;
	colors[ImGuiCol_PlotHistogramHovered] = Pink;

	colors[ImGuiCol_TableHeaderBg] = Surface0;
	colors[ImGuiCol_TableBorderStrong] = Surface1;
	colors[ImGuiCol_TableBorderLight] = Surface0;
	colors[ImGuiCol_TableRowBg] = ImVec4(0, 0, 0, 0);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1, 1, 1, 0.02f);

	colors[ImGuiCol_TextSelectedBg] = Surface2;
	colors[ImGuiCol_DragDropTarget] = Yellow;
	colors[ImGuiCol_NavHighlight] = Mauve;
	colors[ImGuiCol_NavWindowingHighlight] = Text;
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.12f, 0.12f, 0.19f, 0.70f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.12f, 0.12f, 0.19f, 0.70f);

	colors[ImGuiCol_DockingPreview] = Surface1;
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
}

Editor::~Editor()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Editor::Run()
{
	while (!window.ShouldClose())
	{
		Update();
		Render();
	}
}

void Editor::Update()
{
	window.PollEvents(&context);
	context.Info();

	if (Input::GetKey(VK_ESCAPE))
		window.Close();

	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();
	ImGui::NewFrame();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		ImGui::MenuItem("New");
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::MenuItem("Prefrences");
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Help"))
	{
		ImGui::MenuItem("About");
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
	ImGui::PopStyleVar();

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::DockSpaceOverViewport();
	ImGui::PopStyleColor();
	ImGui::ShowDemoWindow();
}

void Editor::Render()
{
	context.Clear(0.0f, 0.4f, 0.2f, 1.0f);
	context.DrawTestCube();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	context.Swap();
}