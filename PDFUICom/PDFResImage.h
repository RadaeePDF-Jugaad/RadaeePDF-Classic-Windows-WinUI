#pragma once

#include "RDUILib.PDFResImage.g.h"
#include "PDFUI3.h"

namespace winrt::RDUILib::implementation
{
    struct PDFResImage : PDFResImageT<PDFResImage>
    {
        PDFResImage(int64_t hand)
        {
            m_hand = (PDF_IMPORTCTX)hand;
        }
        int64_t Handle() { return (int64_t)m_hand; }
        PDF_IMPORTCTX m_hand;
    };
}

namespace winrt::RDUILib::factory_implementation
{
    struct PDFResImage : PDFResImageT<PDFResImage, implementation::PDFResImage>
    {
    };
}
