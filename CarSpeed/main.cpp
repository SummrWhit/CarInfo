#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "qdatamgr.h"
#include "system/error_code.hpp"
#include "pcl/common/common_headers.h"
#include "pcl/io/pcd_io.h"
#include "pcl/visualization/pcl_visualizer.h"
#include "pcl/visualization/cloud_viewer.h"
#include "pcl/console/parse.h"
#include "pointcloud.h"

int user_data;
void viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor (1.0, 0.5, 1.0);
    pcl::PointXYZ o;
    o.x = 1.0;
    o.y = 0;
    o.z = 0;
    viewer.addSphere (o, 0.25, "sphere", 0);
    std::cout << "i only run once" << std::endl;
}

void viewerPsycho (pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned count = 0;
    std::stringstream ss;
    ss << "Once per viewer loop: " << count++;
    viewer.removeShape ("text", 0);
    viewer.addText (ss.str(), 200, 300, "text", 0);
    //FIXME: possible race condition here:
    user_data++;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QDataMgr data_mgr;
    engine.rootContext()->setContextProperty("DATAMGR", &data_mgr);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    pointcloud pc;
    //pc.show();
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    //QVTKWidget* qvtkWidget;
    //boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    //viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
    //viewer->addPointCloud(cloud, "cloud");
    if (pcl::io::loadPCDFile
            ("/home/haoran.wang/Project/carSpeed/CarSpeed/bunny.pcd", *cloud) == -1) {
        PCL_ERROR("Couldn't read that pcd file\n");
        return(-1);
    }

    //pcl::visualization::CloudViewer viewer("viewer");
    //blocks until the cloud is actually rendered
    //viewer.showCloud(cloud);
    //use the following functions to get access to the underlying more advanced/powerful
    //PCLVisualizer
    //This will only get called once
    //viewer.runOnVisualizationThreadOnce (viewerOneOff);
    //This will get called once per visualization iteration
    //viewer.runOnVisualizationThread (viewerPsycho);
    //while (!viewer.wasStopped ())
    //{
    //you can also do cool processing here
    //FIXME: Note that this is running in a separate thread from viewerPsycho
    //and you should guard against race conditions yourself...
    //user_data++;
    //}
    //return 0;

    return app.exec();
}
