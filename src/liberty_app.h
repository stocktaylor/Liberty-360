// liberty - ReXGlue Recompiled Project
//
// Customize your app by overriding virtual hooks from rex::ReXApp.

#pragma once

#include <rex/filesystem.h>
#include <rex/rex_app.h>
#if LIBERTY_LAUNCHER
#include <rexlauncher/launch_menu.h>
#endif

class LibertyApp : public rex::ReXApp {
 public:
  using rex::ReXApp::ReXApp;

  static std::unique_ptr<rex::ui::WindowedApp> Create(
      rex::ui::WindowedAppContext& ctx) {
    return std::unique_ptr<LibertyApp>(new LibertyApp(ctx, "liberty",
        PPCImageConfig));
  }

  // With no --game_data_root, use a "game" folder next to the executable, so a
  // packaged build runs with just `./liberty` (see rextools `rex dist`).
  void OnConfigurePaths(rex::PathConfig& paths) override {
    if (paths.game_data_root.empty()) {
      paths.game_data_root = rex::filesystem::GetExecutableFolder() / "game";
    }
  }

#if LIBERTY_LAUNCHER
  // Launch menu (../rexlauncher): shown in the game window before the game
  // starts; Play hands the window over to the game.
  void OnConfigureFonts(ImFontAtlas* atlas) override {
    rexlauncher::ConfigureFonts(atlas);
  }

  std::optional<rex::PathConfig> OnFinalizePaths(
      const rex::PathConfig& defaults,
      std::function<void(rex::PathConfig)> resume) override {
    rexlauncher::Config menu;
    menu.title = "Grand Theft Auto IV";
    return rexlauncher::Show(imgui_drawer(), app_context(), defaults,
                             std::move(resume), std::move(menu));
  }

  // In-game menu (F1 or Back + Start), same options as the launch menu.
  void OnPostSetup() override {
    rexlauncher::EnableInGameMenu(imgui_drawer(), app_context(), runtime());
  }
#endif  // LIBERTY_LAUNCHER

  // Override virtual hooks for customization:
  // void OnPostInitLogging() override {}
  // void OnPreSetup(rex::RuntimeConfig& config) override {}
  // void OnLoadXexImage(std::string& xex_image) override {}
  // void OnPostLoadXexImage() override {}
  // void OnCreateDialogs(rex::ui::ImGuiDrawer* drawer) override {}
  // std::unique_ptr<rex::ui::ImGuiDialog> CreateAchievementsOverlay() override;
  // std::unique_ptr<rex::ui::AchievementNotificationDialog>
  // CreateAchievementNotificationDialog() override;
  // void OnShutdown() override {}
};
