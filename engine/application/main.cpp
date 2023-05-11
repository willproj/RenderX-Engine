#include "renderxApp.h"

int main()
{
    auto app = engine::app::RenderXApp::getInstance();
    app->init();
    app->run();
    return 0;
}


