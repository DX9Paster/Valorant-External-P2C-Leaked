#pragma once
namespace hotkeys
{
	int aimkey;
	int airstuckey;
	int instares;
}
static int keystatus = 0;
static int realkey = 0;
bool GetKey(int key)
{
	realkey = key;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}

static const char* keyNames[] =
{
	"< KEY >",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};
static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = "Select Key";
	else
		aimkeys = preview_value;

	if (status == 1)
	{

		aimkeys = "Press the Key";
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}

auto drawmenu() -> void
{
	if (GetAsyncKeyState(VK_INSERT) & 1) { Settings::bMenu = !Settings::bMenu; }

	if (Settings::bMenu)
	{
		static int switchTabs;
		ImGuiIO io = ImGui::GetIO();
		ImGui::Begin(XorStr("        Beef Version : 3.0 - Made With Love By Beef#3348 - Discord.gg/fZaGQfXqug - Tickets For Support").c_str(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		ImGui::SetWindowSize(XorStr("        Beef Version : 3.0 - Made With Love By Beef#3348 - Discord.gg/fZaGQfXqug - Tickets For Support").c_str(), ImVec2(647.f, 439.f));
		
		ImGui::SetCursorPos({ 10.f,30.f });

		ImGui::BeginChild("child0", { 175.f,398.f }, true);

		ImGui::SetCursorPos({ 18.f,19.f });
		if (ImGui::Button(XorStr("Aimbot").c_str(), { 137.f,47.f }))
		{
			switchTabs = 0;
		}
		ImGui::SetCursorPos({ 18.f,86.f });
		if (ImGui::Button(XorStr("Visual").c_str(), { 137.f,47.f }))
		{
			switchTabs = 1;
		}
		ImGui::SetCursorPos({ 18.f,155.f });
		if (ImGui::Button(XorStr("Misc").c_str(), { 137.f,47.f }))
		{
			switchTabs = 2;
		}
		ImGui::SetCursorPos({ 25.f,372.f });
		ImGui::PushItemWidth(98.000000);
		ImGui::Text(XorStr("Made By -  Beef#3348").c_str());
		ImGui::PopItemWidth();

		ImGui::SetCursorPos({ 17.f,221.f });
		ImGui::PushItemWidth(140.000000);
		ImGui::Text(XorStr("  Discord.gg/fZaGQfXqug").c_str());
		ImGui::PopItemWidth();

		ImGui::SetCursorPos({ 7.f,245.f });
		ImGui::PushItemWidth(161.000000);
		ImGui::Text("             Menu FPS: 60 ", 20000 / io.Framerate);
		ImGui::PopItemWidth();


		ImGui::EndChild();

		switch (switchTabs) {
		case 0:

			ImGui::SetCursorPos({ 194.f,30.f });

			ImGui::BeginChild("child1", { 440.f,398.f }, true);

			ImGui::SetCursorPos({ 13.f,13.f });
			ImGui::Checkbox(XorStr("Aimbot Enable").c_str(), &Settings::aimbot::aimbot);
			HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);
			ImGui::SetCursorPos({ 13.f,44.f });
			ImGui::PushItemWidth(346.000000);

			ImGui::SetCursorPos({ 13.f,74.f });
			ImGui::Checkbox(XorStr("Enable Smoothing").c_str(), &Settings::aimbot::smooth);
			ImGui::Text(XorStr("Smoothness: ").c_str());
			ImGui::SliderFloat("  ", &Settings::aimbot::smoothness, 1, 5);
			ImGui::PopItemWidth();

			ImGui::SetCursorPos({ 13.f,74.f });
			ImGui::PushItemWidth(346.000000);

			ImGui::PopItemWidth();
			ImGui::SetCursorPos({ 13.f,145.f });
			ImGui::Checkbox(XorStr("Show FOV Circle").c_str(), &Settings::aimbot::drawfov);
			ImGui::Text(XorStr("FOV Value: ").c_str());
			ImGui::SliderFloat("    ", &Settings::aimbot::fov, 10, 300);
			ImGui::SetCursorPos({ 13.f,213.f });
			ImGui::Checkbox(XorStr("Visible Check").c_str(), &Settings::aimbot::vischeck);





			ImGui::EndChild();

			ImGui::SetCursorPos({ 194.f,30.f });

			ImGui::BeginChild("child1", { 440.f,398.f }, true);



			break;
		case 1:
			ImGui::SetCursorPos({ 194.f,30.f });

			ImGui::BeginChild("child1", { 440.f,398.f }, true);

			ImGui::Spacing();
			ImGui::SetCursorPos({ 13.f,20.f });
			ImGui::Checkbox(XorStr("ESP 3D").c_str(), &Settings::Visuals::bBox);
			ImGui::SetCursorPos({ 13.f,50.f });
			ImGui::Checkbox(XorStr("ESP 2D").c_str(), &Settings::Visuals::TDBox);
			ImGui::SetCursorPos({ 13.f,80.f });
			ImGui::Checkbox(XorStr("ESP Corner").c_str(), &Settings::Visuals::bBoxOutlined);
			ImGui::SetCursorPos({ 13.f,110.f });
			ImGui::Checkbox(XorStr("ESP Skeleton").c_str(), &Settings::Visuals::Skeleton);
			ImGui::SetCursorPos({ 13.f,140.f });
			ImGui::Checkbox(XorStr("ESP SnapLine").c_str(), &Settings::Visuals::bSnaplines);
			ImGui::SetCursorPos({ 13.f,170.f });
			ImGui::Checkbox(XorStr("ESP Distance").c_str(), &Settings::Visuals::bDistance);
			ImGui::SetCursorPos({ 13.f,200.f });
			ImGui::Checkbox(XorStr("ESP Health").c_str(), &Settings::Visuals::bHealth);
			ImGui::SetCursorPos({ 13.f,230.f });
			ImGui::Checkbox(XorStr("ESP Head").c_str(), &Settings::Visuals::HeadCircle);
			ImGui::SetCursorPos({ 13.f,260.f });
			
			ImGui::SetCursorPos({ 13.f,290.f });

			ImGui::SetCursorPos({ 13.f,320.f });
			ImGui::SetCursorPos({ 13.f,350.f });

			ImGui::SetCursorPos({ 13.f,380.f });

			ImGui::SetCursorPos({ 13.f,410.f });

			ImGui::SetCursorPos({ 13.f,440.f });

			ImGui::SetCursorPos({ 13.f,470.f });

			ImGui::SetCursorPos({ 13.f,500.f });

			ImGui::SetCursorPos({ 13.f,530.f });

			ImGui::SetCursorPos({ 13.f,560.f });

			ImGui::SetCursorPos({ 13.f,590.f });

			ImGui::EndChild();

			ImGui::SetCursorPos({ 194.f,30.f });

			ImGui::BeginChild("child1", { 440.f,398.f }, true);



			break;
		case 2:
			ImGui::SetCursorPos({ 194.f,30.f });
			ImGui::BeginChild("child1", { 440.f,398.f }, true);
			ImGui::Spacing();
			ImGui::Combo(skCrypt("SELECT ENTITY"), &Settings::misc::enemyselect, Settings::misc::Teams, sizeof(Settings::misc::Teams) / sizeof(*Settings::misc::Teams));
			ImGui::Checkbox("WATERMARK & FPS", &Settings::Visuals::FPS);
			ImGui::Checkbox("DEBUG", &NewFeatures::ActorCountDebug); //still in the works
			ImGui::SliderFloat("HeadBox Size", &Settings::misc::headsize, 100, 35);
			ImGui::SliderFloat("FOV Changer", &Settings::Visuals::fovchangervalue, 0, 1000);
			ImGui::SliderFloat("Radar Entity Size", &Settings::misc::radarentitysize, 1, 5);
			ImGui::SliderFloat("2D Box Thickness", &Settings::Visuals::BoxWidth, 0, 5);
			ImGui::SliderFloat("Radar Size", &Settings::misc::Size, 256, 258);
			ImGui::SliderFloat("Skeleton Thickness", &Settings::Visuals::skeletonwidht, 0, 5);
			ImGui::SliderFloat("Render Distance (m)", &NewFeatures::renderdistance, 0, 750);
			ImGui::TextColored(ImColor(colors::BLAHBLAH[0], colors::BLAHBLAH[1], colors::BLAHBLAH[2], colors::BLAHBLAH[3]), "[DEBUG]: %i ", NewFeatures::curractors);
			ImGui::EndChild();

			break;
		case 3:
			ImGui::SetCursorPos({ 194.f,30.f });

			ImGui::BeginChild("child1", { 440.f,398.f }, true);

			ImGui::SetCursorPos({ 13.f,20.f });
			ImGui::Text(XorStr("Discord Tag : Syntax#1000").c_str());
			ImGui::SetCursorPos({ 13.f,50.f });
			ImGui::Text(XorStr("Discord Server : discord.gg/vhdmNe4VqZ").c_str());
			ImGui::SetCursorPos({ 13.f,80.f });
			ImGui::Text(XorStr("Email : dildoman33@gmail.com ").c_str());



			ImGui::EndChild();

			ImGui::SetCursorPos({ 194.f,30.f });

			ImGui::BeginChild("child1", { 440.f,398.f }, true);

			ImGui::SetCursorPos({ 13.f,213.f });

			ImGui::SetCursorPos({ 13.f,245.f });
			ImGui::EndChild();
			ImGui::End();
		}
	}
}
