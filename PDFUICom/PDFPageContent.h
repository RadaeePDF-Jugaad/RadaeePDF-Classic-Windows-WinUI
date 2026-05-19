#pragma once

#include "RDUILib.PDFPageContent.g.h"
#include "PDFUI3.h"

namespace winrt::RDUILib::implementation
{
    struct PDFPageContent : PDFPageContentT<PDFPageContent>
    {
        PDFPageContent()
        {
            m_hand = PageContent_create();
        }
        ~PDFPageContent()
        {
            PageContent_destroy(m_hand);
        }
        int64_t Handle() { return (int64_t)m_hand; }
        PDF_PAGECONTENT m_hand;
        void ClipPath(winrt::RDUILib::RDPath path, bool winding)
        {
            PageContent_clipPath(m_hand, (PDF_PATH)path.Handle(), winding);
        }
        void DrawForm(winrt::RDUILib::PDFResForm form)
        {
            PageContent_drawForm(m_hand, (PDF_PAGE_FORM)form.Handle());
        }
        void DrawImage(winrt::RDUILib::PDFResImage img)
        {
            PageContent_drawImage(m_hand, (PDF_PAGE_IMAGE)img.Handle());
        }
        void DrawText(winrt::hstring text)
        {
            PageContent_drawTextW(m_hand, text.c_str());
        }
        int DrawText(winrt::hstring text, int align, float width)
        {
            return PageContent_drawText2W(m_hand, text.c_str(), align, width);
        }
        PDFTextRet DrawText(winrt::hstring text, int align, float width, int max_lines)
        {
            int val = PageContent_drawText3W(m_hand, text.c_str(), align, width, max_lines);
            PDFTextRet ret;
            ret.num_unicodes = val & ((1 << 20) - 1);
            ret.num_lines = val >> 20;
            return ret;
        }
        void FillPath(RDPath path, bool winding)
        {
            PageContent_fillPath(m_hand, (PDF_PATH)path.Handle(), winding);
        }
        RDPoint GetTextSize(winrt::hstring text, winrt::RDUILib::PDFResFont pfont, float width, float height, float char_space, float word_space)
        {
            PDF_POINT pt = PageContent_textGetSizeW(m_hand, (PDF_PAGE_FONT)pfont.Handle(), text.c_str(), width, height, char_space, word_space);
            return *(RDPoint*)&pt;
        }
        void GSRestore()
        {
            PageContent_gsRestore(m_hand);
        }
        void GSSave()
        {
            PageContent_gsSave(m_hand);
        }
        void GSSet(winrt::RDUILib::PDFResGState gs)
        {
            PageContent_gsSet(m_hand, (PDF_PAGE_GSTATE)gs.Handle());
        }
        void GSSetMatrix(RDMatrix mat)
        {
            PageContent_gsSetMatrix(m_hand, (PDF_MATRIX)mat.Handle());
        }
        void SetFillColor(unsigned int color)
        {
            PageContent_setFillColor(m_hand, color);
        }
        void SetStrokeCap(int cap)
        {
            PageContent_setStrokeCap(m_hand, cap);
        }
        void SetStrokeColor(unsigned int color)
        {
            PageContent_setStrokeColor(m_hand, color);
        }
        void SetStrokeDash(winrt::array_view<float const> dash, float phase)
        {
            if (dash.size() > 0)
                PageContent_setStrokeDash(m_hand, dash.data(), dash.size(), phase);
            else
                PageContent_setStrokeDash(m_hand, NULL, 0, phase);
        }
        void SetStrokeJoin(int join)
        {
            PageContent_setStrokeJoin(m_hand, join);
        }
        void SetStrokeMiter(float miter)
        {
            PageContent_setStrokeMiter(m_hand, miter);
        }
        void SetStrokeWidth(float w)
        {
            PageContent_setStrokeWidth(m_hand, w);
        }
        void StrokePath(RDPath path)
        {
            PageContent_strokePath(m_hand, (PDF_PATH)path.Handle());
        }
        void TextBegin()
        {
            PageContent_textBegin(m_hand);
        }
        void TextEnd()
        {
            PageContent_textEnd(m_hand);
        }
        void TextMove(float x, float y)
        {
            PageContent_textMove(m_hand, x, y);
        }
        void TextNextLine()
        {
            PageContent_textNextLine(m_hand);
        }
        void TextSetCharSpace(float space)
        {
            PageContent_textSetCharSpace(m_hand, space);
        }
        void TextSetFont(winrt::RDUILib::PDFResFont font, float size)
        {
            PageContent_textSetFont(m_hand, (PDF_PAGE_FONT)font.Handle(), size);
        }
        void TextSetHScale(int scale)
        {
            PageContent_textSetHScale(m_hand, scale);
        }
        void TextSetLeading(float leading)
        {
            PageContent_textSetLeading(m_hand, leading);
        }
        void TextSetRenderMode(int mode)
        {
            PageContent_textSetRenderMode(m_hand, mode);
        }
        void TextSetRise(float rise)
        {
            PageContent_textSetRise(m_hand, rise);
        }
        void TextSetWordSpace(float space)
        {
            PageContent_textSetWordSpace(m_hand, space);
        }
    };
}

namespace winrt::RDUILib::factory_implementation
{
    struct PDFPageContent : PDFPageContentT<PDFPageContent, implementation::PDFPageContent>
    {
    };
}
