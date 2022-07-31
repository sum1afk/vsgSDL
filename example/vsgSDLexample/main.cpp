#include <vsg/all.h>

#ifdef vsgXchange_FOUND
#    include <vsgXchange/all.h>
#endif

#include <vsgSDL/window.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    // set up defaults and read command line arguments to override them
    vsg::CommandLine arguments(&argc, argv);

    // set up vsg::Options to pass in filepaths and ReaderWriter's and other IO related options to use when reading and writing files.
    auto options = vsg::Options::create();
#ifdef vsgXchange_all
    // add vsgXchange's support for reading and writing 3rd party file formats
    options->add(vsgXchange::all::create());
#endif
    options->fileCache = vsg::getEnv("VSG_FILE_CACHE");
    options->paths = vsg::getEnvPaths("VSG_FILE_PATH");
    arguments.read(options);

    // preload model
    vsg::Path filename = "models/teapot.vsgt";
    if (argc > 1) filename = arguments[1];

    if (arguments.errors()) return arguments.writeErrorMessages(std::cerr);

    // load the scene graph
    vsg::ref_ptr<vsg::Node> vsg_scene = vsg::read_cast<vsg::Node>(filename, options);
    if (!vsg_scene) return 0;

    vsgSDL::Window window;

    window.renderInit = [&](const vsg::ref_ptr<vsg::Window> window, const vsg::ref_ptr<vsg::Viewer> viewer, const vsg::ref_ptr<vsg::WindowTraits> traits) {
        // compute the bounds of the scene graph to help position camera
        vsg::ComputeBounds computeBounds;
        vsg_scene->accept(computeBounds);
        vsg::dvec3 centre = (computeBounds.bounds.min + computeBounds.bounds.max) * 0.5;
        double radius = vsg::length(computeBounds.bounds.max - computeBounds.bounds.min) * 0.6;
        double nearFarRatio = 0.001;

        // set up the camera
        auto lookAt = vsg::LookAt::create(centre + vsg::dvec3(0.0, -radius * 3.5, 0.0), centre, vsg::dvec3(0.0, 0.0, 1.0));

        vsg::ref_ptr<vsg::ProjectionMatrix> perspective;
        vsg::ref_ptr<vsg::EllipsoidModel> ellipsoidModel(vsg_scene->getObject<vsg::EllipsoidModel>("EllipsoidModel"));
        if (ellipsoidModel)
        {
            double horizonMountainHeight = 0.0;
            perspective = vsg::EllipsoidPerspective::create(lookAt, ellipsoidModel, 30.0, static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height), nearFarRatio, horizonMountainHeight);
        }
        else
        {
            perspective = vsg::Perspective::create(30.0, static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height), nearFarRatio * radius, radius * 4.5);
        }

        auto camera = vsg::Camera::create(perspective, lookAt, vsg::ViewportState::create(window->extent2D()));

        // add close handler to respond the close window button and pressing escape
        viewer->addEventHandler(vsg::CloseHandler::create(viewer));

        // add trackball to control the Camera
        viewer->addEventHandler(vsg::Trackball::create(camera, ellipsoidModel));

        // add the CommandGraph to render the scene
        auto commandGraph = vsg::createCommandGraphForView(window, camera, vsg_scene);
        viewer->assignRecordAndSubmitTaskAndPresentation({ commandGraph });

        // compile all Vulkan objects and transfer image, vertex and primitive data to GPU
        viewer->compile();
    };

    window.renderDeinit = [](const vsg::ref_ptr<vsg::Viewer> viewer) {
    };

    window.render = [](const vsg::ref_ptr<vsg::Viewer> viewer) {
        viewer->handleEvents();

        viewer->update();

        viewer->recordAndSubmit();

        viewer->present();
    };

    window.focusGained = [](vsg::ref_ptr<vsg::Window> window) {
        if (auto wa = window.cast<vsg::WindowAdapter>(); wa) {
            wa->windowValid = true;
            wa->windowVisible = true;
        }
    };

    window.focusLost = [](vsg::ref_ptr<vsg::Window> window) {
        if (auto wa = window.cast<vsg::WindowAdapter>(); wa)
        {
            wa->windowVisible = false;
        }
    };

    window.textInput = [](const char text[SDL_TEXTINPUTEVENT_TEXT_SIZE]) {
    };

    window.create(
        "SDL_test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1280,
        720,
        SDL_WINDOW_VULKAN,
        false,
        false,
        "");
    while (true) {
        bool scanforcontinouskeyinputs = false;
        if (!window.process(scanforcontinouskeyinputs)) break;
    }

    return 0;
}