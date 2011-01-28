#ifndef VARIABLE_VIEW_PLUGIN_H
#define VARIABLE_VIEW_PLUGIN_H

#include <QWidget>
#include <QDialog>
#include "TargetModels.h"
#include "Plugin.h"
#include "../compiler/compiler.h"

class QLabel;
class QComboBox;

namespace Aseba
{
	/** \addtogroup studio */
	/*@{*/
	
	class TargetVariablesModel;
	
	class LinearCameraViewVariablesDialog : public QDialog
	{
		Q_OBJECT
		
	public:
		QComboBox* redVariable;
		QComboBox* greenVariable;
		QComboBox* blueVariable;
		QComboBox* valuesRanges;
		
		LinearCameraViewVariablesDialog(TargetVariablesModel* variablesModel);
		virtual ~LinearCameraViewVariablesDialog() {}
	};
	
	class LinearCameraViewPlugin: public QWidget, public NodeToolInterface, public InvasivePlugin, public VariableListener
	{
		Q_OBJECT
		
	public:
		LinearCameraViewPlugin(NodeTab* nodeTab);
		
		virtual QWidget* createMenuEntry();
		virtual void closeAsSoonAsPossible();
	
	signals:
		void dialogBoxResult(bool ok);
		
	private slots:
		void setEnabled(bool enabled);
		
	private:
		void enablePlugin();
		void disablePlugin();
		
		virtual void timerEvent ( QTimerEvent * event );
		virtual void variableValueUpdated(const QString& name, const VariablesDataVector& values);
		
	private:
		enum ValuesRange
		{
			VALUES_RANGE_AUTO = 0,
			VALUES_RANGE_8BITS,
			VALUES_RANGE_PERCENT
		} valuesRange;
		QLabel *image;
		QString redName, greenName, blueName;
		unsigned redPos, greenPos, bluePos;
		unsigned redSize, greenSize, blueSize;
		VariablesDataVector red, green, blue;
		unsigned componentsReceived;
	};
	
	/*@}*/
}; // Aseba

#endif
