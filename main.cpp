#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

using namespace std;

struct cube_rotate{

  GLfloat angle, x, y, z;

};

GLfloat angle, fAspect, cube_size;
GLint rot_x, rot_y, crement, x_0, x_k, y_0, y_k, z_0, z_k, gap, gap_crement;

vector<cube_rotate> cube_rotations[3][3][3];

void load_visualization_parameters(void);

void apply_rotation(GLfloat angle){

  vector<cube_rotate> face[3][3];
  int index;
  cube_rotate rotation;


  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j) {

      index = 2 - j%3;

      if(x_0 == x_k){
	rotation = {angle, 1.0, 0.0, 0.0};
	face[index][i] = cube_rotations[x_k][i][j];
      }

      if(y_0 == y_k){
	rotation = {angle, 0.0, 1.0, 0.0};
	face[index][i] = cube_rotations[j][y_k][i];
      }

      if(z_0 == z_k){
	rotation = {-1 * angle, 0.0, 0.0, 1.0};
	face[index][i] = cube_rotations[j][i][z_k];
      }

      face[index][i].push_back(rotation);

    }

  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j) {

      if(x_0 == x_k)
	cube_rotations[x_k][i][j] = face[i][j];

      if(y_0 == y_k)
	cube_rotations[j][y_k][i] = face[i][j];

      if(z_0 == z_k)
	cube_rotations[j][i][z_k] = face[i][j];
    }

}


void reset_selected_face(){

  x_0 = 0;
  x_k = 2;
  y_0 = 0;
  y_k = 2;
  z_0 = 0;
  z_k = 2;

}

void set_camera()
{

  gluLookAt(0,80,200, 0,0,0, 0,1,0);

}

void draw_cube(int x, int y, int z)
{

  vector<cube_rotate> lrot = cube_rotations[x][y][z];

  glPushMatrix();
  glTranslatef((x - 1) * cube_size + x * gap, (y - 1) * cube_size + y * gap, (z - 1) * cube_size + z * gap);

  for(int i = lrot.size() - 1; i >= 0; --i)
    glRotatef(lrot[i].angle, lrot[i].x, lrot[i].y, lrot[i].z);

  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
  glEnd();

  glColor3f(1.0f, 0.5f, 0.0f);
  glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
  glEnd();

  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-cube_size/2, cube_size/2, -cube_size/2);
    glVertex3f(-cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, cube_size/2);
    glVertex3f(cube_size/2, cube_size/2, -cube_size/2);
  glEnd();

  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, -cube_size/2);
    glVertex3f(cube_size/2, -cube_size/2, cube_size/2);
    glVertex3f(-cube_size/2, -cube_size/2, cube_size/2);
  glEnd();

  glPopMatrix();

}
void draw_func(void)
{

  int x = -cube_size, y = -cube_size, z = -cube_size;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  set_camera();
  glRotatef(rot_x, 1.0, 0.0, 0.0);
  glRotatef(rot_y, 0.0, 1.0, 0.0);

  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j)
      for(int k = 0; k < 3; ++k) {

	draw_cube(i, j, k);

      }
  glutSwapBuffers();

}


void init_func (void)
{
  cube_size = 30.0;
  rot_x = 0.0;
  rot_y = 0.0;
  crement = 5;
  gap = 5;
  gap_crement = 3;

  GLfloat ambient_lighte[4]={0.2,0.2,0.2,1.0};
  GLfloat diffuse_light[4]={0.7,0.7,0.7,1.0};
  GLfloat specular_light[4]={1.0, 1.0, 1.0, 1.0};
  GLfloat light_position[4]={0.0, 50.0, 50.0, 1.0};

  GLfloat specularity[4]={1.0,1.0,1.0,1.0};
  GLint material_specularity = 60;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT,GL_SPECULAR, specularity);
  glMateriali(GL_FRONT,GL_SHININESS,material_specularity);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_lighte);


  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_lighte);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light );
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light );
  glLightfv(GL_LIGHT0, GL_POSITION, light_position );

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  angle=45;

}
void load_visualization_parameters(void)
{

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(angle,fAspect,0.4,500);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  set_camera();
}
void reshape_func(GLsizei w, GLsizei h)
{

  if ( h == 0 ) h = 1;

  glViewport(0, 0, w, h);
  fAspect = (GLfloat)w/(GLfloat)h;
  load_visualization_parameters();
}
void keyboard_func(unsigned char key, int x, int y)
{

  switch(key) {

    case '+':
      gap += gap_crement;
      break;

    case '-':
      gap -= gap_crement;
      break;

    case 'L':
    case 'l':
      rot_y = (rot_y - crement) % 360;
      break;

    case 'J':
    case 'j':
      rot_y = (rot_y + crement) % 360;
      break;

    case 'I':
      rot_x = (rot_x + crement) % 360;
      break;

    case 'K':
    case 'k':
      rot_x = (rot_x - crement) % 360;
      break;

    case 'Q':
    case 'q':
      reset_selected_face();
      x_0 = 0;
      x_k = 0;
      break;

    case 'W':
    case 'w':
      reset_selected_face();
      x_0 = 1;
      x_k = 1;
      break;

    case 'E':
    case 'e':
      reset_selected_face();
      x_0 = 2;
      x_k = 2;
      break;


    case 'A':
    case 'a':
      reset_selected_face();
      y_0 = 0;
      y_k = 0;
      break;

    case 'S':
    case 's':
      reset_selected_face();
      y_0 = 1;
      y_k = 1;
      break;

    case 'D':
    case 'd':
      reset_selected_face();
      y_0 = 2;
      y_k = 2;
      break;


    case 'C':
    case 'c':
      reset_selected_face();
      z_0 = 0;
      z_k = 0;
      break;

    case 'X':
    case 'x':
      reset_selected_face();
      z_0 = 1;
      z_k = 1;
      break;

    case 'Z':
    case 'z':
      reset_selected_face();
      z_0 = 2;
      z_k = 2;
      break;


    case 'U':
    case 'u':
      apply_rotation(-90);
      break;

    case 'O':
    case 'o':
      apply_rotation(90);
      break;



    default:
      break;

  }

  glutPostRedisplay();

}


void mouse_func(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
    if (state == GLUT_DOWN) {
	    if (angle >= 10) angle -= 5;
    }
  if (button == GLUT_RIGHT_BUTTON)
    if (state == GLUT_DOWN) {
	    if (angle <= 130) angle += 5;
    }
  load_visualization_parameters();
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400,350);
  glutCreateWindow("RUBIK'S CUBE");
  glutDisplayFunc(draw_func);
  glutReshapeFunc(reshape_func);
  glutMouseFunc(mouse_func);
  glutKeyboardFunc(keyboard_func);
  init_func();
  glutMainLoop();
}
