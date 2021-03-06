#include <QtCore/QDebug>

#define PCL_NO_PRECOMPILE
#define _OPENMP
#include "../pcl_bugfix/mls2.h"

#include "../include/movingleastsquares.h"

using namespace registar;

MovingLeastSquares::MovingLeastSquares(){}

MovingLeastSquares::~MovingLeastSquares(){}

void MovingLeastSquares::filter(CloudDataConstPtr &cloudData, QVariantMap parameters, CloudDataPtr &cloudData_filtered)
{
	pcl::MovingLeastSquares2<PointType, PointType>::UpsamplingMethod method = 
	(pcl::MovingLeastSquares2<PointType,PointType>::UpsamplingMethod)(parameters["method"].toInt());

	bool computeNormal = parameters["computeNormal"].toBool();
	float searchRadius = parameters["searchRadius"].toFloat();
	QString distinctCloudName = parameters["distinctCloudName"].toString();
	float upsamplingRadius = parameters["upsamplingRadius"].toFloat();
	float stepSize = parameters["stepSize"].toFloat();
	int density = parameters["density"].toInt();
	float voxelSize = parameters["voxelSize"].toFloat();
	int dilationIterations = parameters["dilationIterations"].toInt();

	bool use_scpu = parameters["use_scpu"].toBool();
	bool use_mcpu = parameters["use_mcpu"].toBool();
	bool use_gpu = parameters["use_gpu"].toBool();

	qDebug() << "Upsampling Method = " << QString::number(method);
	qDebug() << "Compute Normal = " << computeNormal;
	qDebug() << "Search Radius = " << QString::number(searchRadius);
	qDebug() << "Distinct Cloud Name = " << distinctCloudName;
	qDebug() << "Upsampling Radius = " << QString::number(upsamplingRadius) 
				<< ", Step Size = " << QString::number(stepSize);
	qDebug() << "Point Density = " << QString::number(density);
	qDebug() << "Dilation Voxel Size = " << QString::number(voxelSize) 
				<< ", Dilation Iterations = " << QString::number(dilationIterations);

	qDebug() << "use_scpu : " << use_scpu;
	qDebug() << "use_mcpu : " << use_mcpu;
	qDebug() << "use_gpu : " << use_gpu;	

	qDebug() << "Cloud Size Before : " << cloudData->size();

	pcl::MovingLeastSquares2<PointType, PointType>::Ptr mls;

	if (use_scpu)
	{
		mls.reset(new pcl::MovingLeastSquares2<PointType, PointType>);
	}
	else if (use_mcpu)
	{
		int threads = omp_get_num_procs();
		std::cout << threads << "threads" << std::endl;
		mls.reset(new pcl::MovingLeastSquaresOMP2<PointType, PointType>(threads));
	}
	else if (use_gpu)
	{
		int threads = omp_get_num_procs();
		std::cout << threads << " threads" << std::endl;
		mls.reset(new pcl::MovingLeastSquaresOMP2<PointType, PointType>(threads));
	}

	//pcl::MovingLeastSquaresOMP2<PointType, PointType> mls(8);
	pcl::search::KdTree<PointType>::Ptr tree (new pcl::search::KdTree<PointType>);
	mls->setSearchMethod(tree);
	mls->setPolynomialFit(true);
	mls->setInputCloud(cloudData);
	mls->setUpsamplingMethod(method);
	mls->setComputeNormals(computeNormal);
	mls->setSearchRadius(searchRadius);
	//mls.setDistinctCloud(PointCloudInConstPtr distinct_cloud);
	mls->setUpsamplingRadius(upsamplingRadius);
	mls->setUpsamplingStepSize(stepSize);
	mls->setPointDensity(density);
	mls->setDilationVoxelSize(voxelSize);
	mls->setDilationIterations(dilationIterations);
	cloudData_filtered.reset(new CloudData);
	mls->process(*cloudData_filtered);
	
	qDebug() << "Cloud Size After : " << cloudData_filtered->size();
}