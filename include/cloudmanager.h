#ifndef CLOUDMANAGER_H
#define CLOUDMANAGER_H

#include <QtCore/QObject>

#ifndef Q_MOC_RUN
#include "cloud.h"
#endif

namespace registar
{
	class CloudManager : public QObject
	{
		Q_OBJECT

	public:
		CloudManager(QObject *parent = 0);
		virtual ~CloudManager();

		Cloud* addCloud(CloudDataPtr cloudData, const Polygons &polygons, Cloud::FromWhere fromWhere,
			const QString &fileName = "", const Eigen::Matrix4f &transformation = Eigen::Matrix4f::Identity() );
		void removeCloud(const QString &cloudName);
		Cloud* getCloud(const QString &cloudName);

		QList<Cloud*> getAllClouds();
		QStringList getAllCloudNames();

	private:
		QString generateCloudName();
	};
}

#endif