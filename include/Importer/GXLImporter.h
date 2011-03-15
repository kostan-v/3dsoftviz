#ifndef Importer_GXLImporter_H
#define Importer_GXLImporter_H
//-----------------------------------------------------------------------------
#include "Importer/StreamImporter.h"
#include "Importer/GraphOperations.h"
#include "Importer/ReadNodesStore.h"
//-----------------------------------------------------------------------------
#include <QtXml/QXmlStreamReader>
//-----------------------------------------------------------------------------

namespace Importer {

/**
 * \brief Imports graph data from data in GXL format.
 */
class GXLImporter
	: public StreamImporter {

public:

	/***/
	virtual ~GXLImporter (void) {};

	/***/
	virtual bool import (
		ImporterContext &context
	);

private:

	/**
	 * <graph> XML node must already have been processed
	 * </graph> XML node is processed by this function
	 * [recursive]
	 */
	bool parseGraph (void);

private:

	// context
	ImporterContext *context_;

	// helpers
	std::auto_ptr<QXmlStreamReader> xml_;
	std::auto_ptr<GraphOperations> graphOp_;
	std::auto_ptr<ReadNodesStore> readNodes_;

	//default types
	Data::Type *edgeType_;
	Data::Type *nodeType_;

}; // class

} // namespace

#endif // Importer_GXLImporter_H
