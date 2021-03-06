#include "viewer.h"
#include "camera.h"

using namespace Eigen;

Viewer::Viewer()
  : _winWidth(0), _winHeight(0)
{
}

Viewer::~Viewer()
{
}

////////////////////////////////////////////////////////////////////////////////
// GL stuff

// initialize OpenGL context
void Viewer::init(int w, int h){
    loadShaders();

    //if(!_mesh.load(DATA_DIR"/models/test.off")) exit(1);
    //====== BEWARE MODIF BELOW ======
    if(!_mesh.load("C:/Users/User/Documents/ENSC/3A/Prog3D/TD2-OpenGL/mds3d_td3_enseirb/data/models/monkey.obj")) exit(1);
    _mesh.initVBA();

    reshape(w,h);
    _trackball.setCamera(&_cam);
}

void Viewer::reshape(int w, int h){
  std::cout << "entered reshape";
    _winWidth = w;
    _winHeight = h;
    _cam.setViewport(w,h);
    // Definir zone tracé -> toute la fenêtre
    glViewport(0, 0, _winWidth, _winHeight);
}


/*!
   callback to draw graphic primitives
 */
void Viewer::drawScene()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.8,0.8,0.8,1);
  // TODO : bon ordre ?
  _shader.activate();
  _mesh.draw(_shader);
  _shader.deactivate();
}

void Viewer::drawScene2D()
{
  glViewport(0, 0, _winWidth, _winHeight);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Matrix4f M;
  M.setIdentity();
  glUniformMatrix4fv(_shader.getUniformLocation("obj_mat"), 1, GL_FALSE, M.data());

  _shader.activate();
  _mesh.draw(_shader);
  _shader.deactivate();
}


void Viewer::updateAndDrawScene()
{
  drawScene2D();
}

void Viewer::loadShaders()
{
    // Here we can load as many shaders as we want, currently we have only one:
    //_shader.loadFromFiles(DATA_DIR"/shaders/simple.vert", DATA_DIR"/shaders/simple.frag");
    _shader.loadFromFiles("C:/Users/User/Documents/ENSC/3A/Prog3D/TD2-OpenGL/mds3d_td3_enseirb/data/shaders/simple.vert",
      "C:/Users/User/Documents/ENSC/3A/Prog3D/TD2-OpenGL/mds3d_td3_enseirb/data/shaders/simple.frag");
    checkError();
}

////////////////////////////////////////////////////////////////////////////////
// Events

/*!
   callback to manage keyboard interactions
   You can change in this function the way the user
   interact with the application.
 */
void Viewer::keyPressed(int key, int action, int /*mods*/)
{
  if(key == GLFW_KEY_R && action == GLFW_PRESS)
  {
    loadShaders();
  }

  if(action == GLFW_PRESS || action == GLFW_REPEAT )
  {
    if (key==GLFW_KEY_UP)
    {
    }
    else if (key==GLFW_KEY_DOWN)
    {
    }
    else if (key==GLFW_KEY_LEFT)
    {
    }
    else if (key==GLFW_KEY_RIGHT)
    {
    }
    else if (key==GLFW_KEY_PAGE_UP)
    {
    }
    else if (key==GLFW_KEY_PAGE_DOWN)
    {
    }
  }
}

/*!
   callback to manage mouse : called when user press or release mouse button
   You can change in this function the way the user
   interact with the application.
 */
void Viewer::mousePressed(GLFWwindow */*window*/, int /*button*/, int action)
{
  if(action == GLFW_PRESS)
  {
      _trackingMode = TM_ROTATE_AROUND;
      _trackball.start();
      _trackball.track(_lastMousePos);
  }
  else if(action == GLFW_RELEASE)
  {
      _trackingMode = TM_NO_TRACK;
  }
}


/*!
   callback to manage mouse : called when user move mouse with button pressed
   You can change in this function the way the user
   interact with the application.
 */
void Viewer::mouseMoved(int x, int y)
{
    if(_trackingMode == TM_ROTATE_AROUND)
    {
        _trackball.track(Vector2i(x,y));
    }

    _lastMousePos = Vector2i(x,y);
}

void Viewer::mouseScroll(double /*x*/, double y)
{
  _cam.zoom(-0.1*y);
}

void Viewer::charPressed(int /*key*/)
{
}
