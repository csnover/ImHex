#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <list>
#include <vector>

#include <hex/ui/view.hpp>

struct GLFWwindow;
struct ImGuiSettingsHandler;


namespace hex {

    void nativeErrorMessage(const std::string &message);

    class Window {
    public:
        Window();
        ~Window();

        void loop();
        void fullFrame();

        static void initNative();

        void resize(i32 width, i32 height);

    private:
        void setupNativeWindow();
        void beginNativeWindowFrame();
        void endNativeWindowFrame();
        void drawTitleBar() const;

        void frameBegin();
        void frame();
        void frameEnd();

        void processEvent() { this->m_hadEvent = true; }

        void initGLFW();
        void initImGui();
        void exitGLFW();
        void exitImGui();

        void registerEventHandlers();

        GLFWwindow *m_window = nullptr;

        std::string m_windowTitle;

        double m_lastStartFrameTime = 0;
        double m_lastFrameTime = 0;

        ImGuiExt::Texture m_logoTexture;

        std::mutex m_popupMutex;
        std::list<std::string> m_popupsToOpen;
        std::vector<int> m_pressedKeys;

        bool m_buttonDown = false;

        bool m_hadEvent = false;
        bool m_frameRateTemporarilyUnlocked = false;
        double m_frameRateUnlockTime = 0;

        bool m_anyViewsOpen = false;

        ImGuiExt::ImHexCustomData m_imguiCustomData;
    };

}