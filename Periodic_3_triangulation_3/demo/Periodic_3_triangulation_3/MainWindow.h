#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QFile>
#include <QTextStream>
#include "Scene.h"

class MainWindow : public QMainWindow
{

  Q_OBJECT

public:
  MainWindow(QWidget* parent = 0) {
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    s = new Scene(ui);

    // QGLViewer drawing signals
    connect(ui->viewer, SIGNAL(viewerInitialized()), s, SLOT(init()));
    connect(ui->viewer, SIGNAL(drawNeeded()), s, SLOT(draw()));

    // divers
    connect(s, SIGNAL(message(const QString&, int)),
	    ui->statusBar, SLOT(showMessage(const QString&, int)));

    // File menu:
    connect(ui->actionLoad_Points, SIGNAL(triggered()),
	    s, SLOT(load_points()));

    // Init menu:
    connect(ui->actionEmpty_scene, SIGNAL(triggered()),
	    s, SLOT(init_scene_empty()));
    connect(ui->actionSingle_Point, SIGNAL(triggered()),
	    s, SLOT(init_scene_single()));
    connect(ui->actionRandom_Point_Set, SIGNAL(triggered()),
	    s, SLOT(init_scene_random()));
    connect(ui->actionRandom_Points_in_Plane, SIGNAL(triggered()),
	    s, SLOT(init_scene_plane()));
    connect(ui->actionPoint_grid, SIGNAL(triggered()),
	    s, SLOT(init_scene_grid()));

    // Actions menu:
    connect(ui->actionFlying_ball, SIGNAL(toggled(bool)),
	    s, SLOT(toggle_flying_ball(bool)));
    connect(ui->actionPause, SIGNAL(toggled(bool)),
	    s, SLOT(toggle_pause(bool)));

    connect(ui->actionInsert_point, SIGNAL(triggered()),
	    s, SLOT(insert_mp()));
    connect(ui->actionInsert_random_point, SIGNAL(triggered()),
	    s, SLOT(insert_random()));

    connect(ui->actionGrab_image, SIGNAL(triggered()),
	    s, SLOT(grab_image()));

    // Features menu:
    connect(ui->actionPoint_location, SIGNAL(toggled(bool)),
	    s, SLOT(toggle_dlocate(bool)));
    connect(ui->actionConflict_region, SIGNAL(toggled(bool)),
	    s, SLOT(toggle_dconflict(bool)));

    // Options menu:
    connect(ui->actionWireframe, SIGNAL(toggled(bool)),
	    s, SLOT(toggle_wireframe(bool)));
    connect(ui->actionPlanar_triangulation, SIGNAL(toggled(bool)),
	    s, SLOT(toggle_in_plane(bool)));

    connect(ui->actionDraw_1_sheeted_covering, SIGNAL(toggled(bool)),
	    s, SLOT(toggle_force_1cover(bool)));
    connect(ui->actionDraw_bordering_cells_multiply, SIGNAL(toggled(bool)),
	    s, SLOT(toggle_multiple_cells(bool)));

    connect(ui->actionDraw_segments, SIGNAL(triggered()),
	    s, SLOT(trigger_draw_type_segment()));
    connect(ui->actionDraw_triangles, SIGNAL(triggered()),
	    s, SLOT(trigger_draw_type_triangle()));
    connect(ui->actionDraw_tetrahedra, SIGNAL(triggered()),
	    s, SLOT(trigger_draw_type_tetrahedron()));

    connect(ui->actionDraw_cube_square, SIGNAL(toggled(bool)),
	    s, SLOT(toggle_ddomain(bool)));

    connect(ui->actionClip_along_the_cube_square, SIGNAL(toggled(bool)),
	    s, SLOT(toggle_cube_clipping(bool)));
    connect(ui->action2_color_clipping, SIGNAL(toggled(bool)),
	    s, SLOT(toggle_two_color_clipping(bool)));

    // Help menu:
    connect(ui->actionDemo_Help, SIGNAL(triggered()),
            this, SLOT(help()));
    connect(ui->actionAbout_CGAL, SIGNAL(triggered()),
            this, SLOT(about_CGAL()));
    connect(ui->actionAbout, SIGNAL(triggered()),
            this, SLOT(about()));

  }

  ~MainWindow() {
    delete(ui);
    delete(s);
  }

public slots:
  void help() {
    showFileBox("Demo manual","resources/about_help.html");
  }
  
  void about() {
    showFileBox("About the demo...","resources/about.html");
  }

  void about_CGAL() {
    showFileBox("About CGAL...","resources/about_CGAL.html");
  }

private:
  void showFileBox(QString title, QString fileName) {
    QFile textFile(fileName);
    textFile.open(QIODevice::ReadOnly);
    QMessageBox mb(QMessageBox::NoIcon,
	title,
	QTextStream(&textFile).readAll(),
	QMessageBox::Ok,
	this);
    mb.exec();
  }

public:
  Ui::MainWindow* ui;
  Scene* s;
};
