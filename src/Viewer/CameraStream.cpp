#include "Viewer/CameraStream.h"
#include <QDebug>
#include <opencv2/highgui/highgui.hpp>
#include "Util/ApplicationConfig.h"


using namespace Vwr;

CameraStream::CameraStream(osg::Geometry *geom) : QObject(), osg::Image()
{
	mGeom	= geom;
	mWidth	= 0;
	mHeight = 0;

	cv::Mat cvImg(480,640, CV_8UC3, CV_RGB(0,0,0));

	updateBackgroundImage( cvImg);
}

CameraStream::~CameraStream(){}

void CameraStream::updateBackgroundImage( cv::Mat cvImg)
{
	if(cvImg.empty()) {
		qDebug() << "CameraStream::updateBackgroundImage(): warning, cvImg is empty!";
		return;
	}

	// update geometry coordinates if thare are different dimensions of image,
	// becasuse probebly changed it ratio of sides
	if(mGeom != NULL ){
		if( cvImg.cols != mWidth || mHeight != cvImg.rows){
			mWidth	= cvImg.cols;
			mHeight = cvImg.rows;
			updateGeometryCoords( mWidth, mHeight);
		}
	}

	// There will be probably needed refactoring on MAC OS
#ifdef WIN32
	IplImage *iplImg = cvCloneImage( &(IplImage)cvImg);

	setImage( iplImg->width, iplImg->height,
			  3, GL_RGB, GL_RGB,
			  GL_UNSIGNED_BYTE,
			  (unsigned char*) iplImg->imageData,
			  NO_DELETE, 1);
#else
	setImage(cvImg.cols, cvImg.rows, 3,
			 GL_RGB, GL_RGB, GL_UNSIGNED_BYTE,
			 (unsigned char*) cvImg.data,
			 NO_DELETE, 1);
#endif

	dirty();

}

void CameraStream::updateGeometryCoords(int width, int height)
{
	float x;
	x = ((float)width) / ((float)height);

	osg::Vec3Array* coords = (osg::Vec3Array*) mGeom->getVertexArray();
	(*coords)[0].set( -x, 1.5f, -1.0f );
	(*coords)[1].set(  x, 1.5f, -1.0f );
	(*coords)[2].set(  x, 1.5f,  1.0f );
	(*coords)[3].set( -x, 1.5f,  1.0f );

	mGeom->dirtyDisplayList();  // update changes

}
