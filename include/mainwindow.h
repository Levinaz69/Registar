#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "../build/ui/ui_MainWindow.h"

namespace registar
{
	class CloudManager;
	class CloudVisualizer;
	class PairwiseRegistrationManager;
	class RegistrationDataManager;
	class CycleRegistrationManager;
}

class EuclideanClusterExtractionDialog;
class VoxelGridDialog;
class MovingLeastSquaresDialog;
class BoundaryEstimationDialog;
class OutliersRemovalDialog;
class NormalFieldDialog;
class VirtualScanDialog;
class DepthCameraDialog;
class AddNoiseDialog;
class TransformationDialog;
class SaveContentDialog;
class HausdorffDistanceDialog;
class ColorFieldDialog;
class GenerateOutliersDialog;

class PairwiseRegistrationDialog;
class BatchPairwiseRegistrationDialog;

class DiagramWindow;
class GlobalRegistrationDialog;

class ManualRegistration;

class Tang2014Dialog;

class BackgroundColorDialog; 


class MainWindow : public QMainWindow, public Ui_MainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();
	
protected:
	void changeEvent(QEvent *event);
	void closeEvent(QCloseEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);

private:
	void registerMetaType();
	void readSettings();
	void writeSettings();
	bool okToContinue();
	QString strippedName(const QString &fullFileName);

	registar::CloudManager *cloudManager;
	registar::CloudVisualizer *cloudVisualizer;
	EuclideanClusterExtractionDialog *euclideanClusterExtractionDialog;
	VoxelGridDialog *voxelGridDialog;
	MovingLeastSquaresDialog *movingLeastSquaresDialog;
	BoundaryEstimationDialog *boundaryEstimationDialog;
	OutliersRemovalDialog *outliersRemovalDialog;
	NormalFieldDialog *normalFieldDialog;
	VirtualScanDialog *virtualScanDialog;
	DepthCameraDialog *depthCameraDialog;
	AddNoiseDialog *addNoiseDialog;
	TransformationDialog *transformationDialog;
	SaveContentDialog *saveContentDialog;
	HausdorffDistanceDialog *hausdorffDistanceDialog;
	ColorFieldDialog *colorFieldDialog;
	GenerateOutliersDialog *generateOutliersDialog;

    PairwiseRegistrationDialog *pairwiseRegistrationDialog;
    BatchPairwiseRegistrationDialog *batchPairwiseRegistrationDialog;
	registar::PairwiseRegistrationManager *pairwiseRegistrationManager;
	registar::RegistrationDataManager *registrationDataManager;

	DiagramWindow *diagramWindow;
	GlobalRegistrationDialog *globalRegistrationDialog;
	registar::CycleRegistrationManager *cycleRegistrationManager;

	ManualRegistration *manualRegistration;

	Tang2014Dialog *tang2014Dialog;

	BackgroundColorDialog *backgroundColorDialog;

	QString currentDirectory;

private slots:
	void on_aboutAction_triggered();
	void on_openAction_triggered();
	bool on_saveAction_triggered();
	bool on_saveAsAction_triggered();

	void on_showCloudBrowserAction_toggled(bool isChecked);
	void on_showPointBrowserAction_toggled(bool isChecked);

	void on_cloudBrowser_cloudVisibleStateChanged(QStringList cloudNameList, bool isVisible);
	
	void on_colorNoneAction_toggled(bool isChecked);
	void on_colorOriginalAction_toggled(bool isChecked);
	void on_colorCustomAction_toggled(bool isChecked);
	void on_drawNormalAction_toggled(bool isChecked);
	void on_drawAxisAction_toggled(bool isChecked);
	void on_drawOrientationMarkerAction_toggled(bool isChecked);
	void on_registrationModeAction_toggled(bool isChecked);
	void on_drawBoundaryAction_toggled(bool isChecked);

	void on_euclideanClusterExtractionAction_triggered();
	void on_voxelGridAction_triggered();
	void on_movingLeastSquaresAction_triggered();
	void on_boundaryEstimationAction_triggered();
	void on_outliersRemovalAction_triggered();

	void on_pairwiseRegistrationAction_triggered();
    void on_batchPairwiseRegistrationAction_triggered();

	void on_diagramAction_triggered();
	void on_globalRegistrationAction_triggered();
	void on_confirmRegistrationAction_triggered();
	void on_applyTransformationAction_triggered();
	void on_forceRigidRegistrationAction_triggered();

	void on_euclideanClusterExtractionDialog_sendParameters(QVariantMap parameters);
	void on_voxelGridDialog_sendParameters(QVariantMap parameters);
	void on_movingLeastSquaresDialog_sendParameters(QVariantMap parameters);
	void on_boundaryEstimationDialog_sendParameters(QVariantMap parameters);
	void on_outliersRemovalDialog_sendParameters(QVariantMap parameters);

	void on_normalFieldAction_triggered();
	void on_normalFieldDialog_sendParameters(QVariantMap parameters);
	void on_addNoiseAction_triggered();
	void on_addNoiseDialog_sendParameters(QVariantMap parameters);
	void on_transformationAction_triggered();
	void on_transformationDialog_sendParameters(QVariantMap parameters);
	void on_hausdorffDistanceAction_triggered();
	void on_hausdorffDistanceDialog_sendParameters(QVariantMap parameters);
	void on_colorFieldAction_triggered();
	void on_colorFieldDialog_sendParameters(QVariantMap parameters);
	void on_generateOutliersAction_triggered();
	void on_generateOutliersDialog_sendParameters(QVariantMap parameters);
	void on_generateOutliersDialog_boundingBox();

	void on_virtualScanAction_triggered();
	void on_virtualScanDialog_sendParameters(QVariantMap parameters);

	void on_depthCameraAction_triggered();
	void on_depthCameraDialog_sendParameters(QVariantMap parameters);

	void on_concatenationAction_triggered();
	void on_removeNaNAction_triggered();

	void on_pairwiseRegistrationDialog_sendParameters(QVariantMap parameters);
	void on_globalRegistrationDialog_sendParameters(QVariantMap parameters);

	void on_tang2014Action_triggered();
	void on_tang2014Dialog_sendParameters(QVariantMap parameters);

	void on_backgroundColorAction_triggered();
	void on_backgroundColorDialog_sendParameters(QVariantMap parameters);
};

#endif 
