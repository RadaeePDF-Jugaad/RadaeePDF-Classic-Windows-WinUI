#pragma once

#include "RDUILib.PDFImportor.g.h"
#include "PDFUI3.h"

namespace winrt::RDUILib::implementation
{
    struct PDFImportor : PDFImportorT<PDFImportor>
    {
        PDFImportor(int64_t doc, int64_t hand)
        {
            m_doc = (PDF_DOC)doc;
            m_hand = (PDF_IMPORTCTX)hand;
        }
        ~PDFImportor()
        {
            Document_importEnd(m_doc, m_hand);
        }
        int64_t Handle() { return (int64_t)m_hand; }
        PDF_DOC m_doc;
        PDF_IMPORTCTX m_hand;
		bool ImportPage(int32_t srcno, int32_t dstno)
		{
			return Document_importPage(m_doc, m_hand, srcno, dstno);
		}
	};
}

namespace winrt::RDUILib::factory_implementation
{
    struct PDFImportor : PDFImportorT<PDFImportor, implementation::PDFImportor>
    {
    };
}
