#pragma once

#include "RDUILib.PDFPage.g.h"
#include "PDFUI3.h"
char* cvt_str_cstr(winrt::hstring str);
winrt::hstring cvt_cstr_str(const char* str);

namespace winrt::RDUILib::implementation
{
    struct PDFPage : PDFPageT<PDFPage>
    {
        //PDFPage() = default;
        PDFPage(int64_t hand)
        {
            m_page = (PDF_PAGE)hand;
        }
        virtual ~PDFPage()
        {
            //Close();
        }
        int64_t Handle()
        {
            return (int64_t)m_page;
        }
        void Close()
        {
            if (m_page)
            {
                Page_close(m_page);
                m_page = NULL;
            }
        }
        RDRect CropBox()
        {
            PDF_RECT rc;
            if (!Page_getCropBox(m_page, &rc))
            {
                rc.left = 0;
                rc.top = 0;
                rc.right = 0;
                rc.bottom = 0;
            }
            return *(RDRect*)&rc;
        }
        RDRect MediaBox()
        {
            PDF_RECT rc;
            if (!Page_getMediaBox(m_page, &rc))
            {
                rc.left = 0;
                rc.top = 0;
                rc.right = 0;
                rc.bottom = 0;
            }
            return *(RDRect*)&rc;
        }
        RDRect GetContentBox()
        {
            PDF_RECT rc;
            if (!Page_getContentBox(m_page, &rc))
            {
                rc.left = 0;
                rc.top = 0;
                rc.right = 0;
                rc.bottom = 0;
            }
            return *(RDRect*)&rc;
        }
        bool AddAnnotAttachment(RDRect rect, winrt::hstring path, int icon)
        {
            char* tmp = cvt_str_cstr(path);
            bool ret = Page_addAnnotAttachment(m_page, tmp, icon, (const PDF_RECT*)&rect);
            free(tmp);
            return ret;
        }
        bool AddAnnotBitmap(PDFDocImage img, RDRect rect)
        {
            return Page_addAnnotBitmap2(m_page, (PDF_DOC_IMAGE)img.Handle(), (const PDF_RECT*)&rect);
        }
        bool AddAnnotBitmap(PDFDocImage img, RDMatrix mat, RDRect rect)
        {
            return Page_addAnnotBitmap(m_page, (PDF_MATRIX)mat.Handle(), (PDF_DOC_IMAGE)img.Handle(), (const PDF_RECT*)&rect);
        }
        bool AddAnnotEditbox(RDRect rect, unsigned int line_clr, float line_w, unsigned int fill_clr, float tsize, unsigned int text_clr)
        {
            return Page_addAnnotEditbox2(m_page, (const PDF_RECT*)&rect, line_clr, line_w, fill_clr, tsize, text_clr);
        }
        bool AddAnnotEllipse(RDRect rect, float width, unsigned int color, unsigned int icolor)
        {
            return Page_addAnnotEllipse2(m_page, (const PDF_RECT*)&rect, width, color, icolor);
        }
        bool AddAnnotInk(RDInk ink)
        {
            return Page_addAnnotInk2(m_page, (PDF_INK)ink.Handle());
        }
        bool AddAnnotLine(float x1, float y1, float x2, float y2, int style1, int style2, float width, unsigned int color, unsigned int icolor)
        {
            PDF_POINT pt1;
            PDF_POINT pt2;
            pt1.x = x1;
            pt1.y = y1;
            pt2.x = x2;
            pt2.y = y2;
            return Page_addAnnotLine2(m_page, &pt1, &pt2, style1, style2, width, color, icolor);
        }
        bool AddAnnotMarkup(int ci1, int ci2, unsigned int color, int type)
        {
            return Page_addAnnotMarkup2(m_page, ci1, ci2, color, type);
        }
        bool AddAnnotPolygon(RDPath path, unsigned int color, unsigned int fill_color, float width)
        {
            if (!path) return false;
            return Page_addAnnotPolygon(m_page, (PDF_PATH)path.Handle(), color, fill_color, width);
        }
        bool AddAnnotPolyline(RDPath path, unsigned int color, int style1, int style2, unsigned int fill_color, float width)
        {
            if (!path) return false;
            return Page_addAnnotPolyline(m_page, (PDF_PATH)path.Handle(), style1, style2, color, fill_color, width);
        }
        bool AddAnnotPopup(PDFAnnot parent, RDRect rect, bool open)
        {
            return Page_addAnnotPopup(m_page, (PDF_ANNOT)parent.Handle(), (const PDF_RECT*)&rect, open);
        }
        bool AddAnnotRect(RDRect rect, float width, unsigned int color, unsigned int icolor)
        {
            return Page_addAnnotRect2(m_page, (const PDF_RECT*)&rect, width, color, icolor);
        }
        bool AddAnnotRichMedia(winrt::hstring path_player, winrt::hstring path_content, int type, PDFDocImage img, RDRect rect)
        {
            return Page_addAnnotRichMedia(m_page, path_player, path_content, type, (PDF_DOC_IMAGE)img.Handle(), (const PDF_RECT*)&rect);
        }
        bool AddAnnotTextNote(float x, float y)
        {
            return Page_addAnnotText2(m_page, x, y);
        }
        bool AddAnnotURI(RDRect rect, winrt::hstring uri)
        {
            char* tmp = cvt_str_cstr(uri);
            bool ret = Page_addAnnotURI2(m_page, (const PDF_RECT*)&rect, tmp);
            free(tmp);
            return ret;
        }
        bool AddContent(PDFPageContent content, bool flush)
        {
            return Page_addContent(m_page, (PDF_PAGECONTENT)content.Handle(), flush);
        }
        RDUILib::PDFResFont AddResFont(RDUILib::PDFDocFont font);
        RDUILib::PDFResForm AddResForm(RDUILib::PDFDocForm form);
        RDUILib::PDFResGState AddResGState(RDUILib::PDFDocGState gs);
        RDUILib::PDFResImage AddResImage(RDUILib::PDFDocImage image);
        bool FlatAnnots()
        {
            return Page_flate(m_page);
        }
        RDUILib::PDFAnnot GetAnnot(float x, float y);
        RDUILib::PDFAnnot GetAnnot(int index);
        RDUILib::PDFFinder GetFinder(winrt::hstring key, bool match_case, bool whole_word);
        RDUILib::PDFFinder GetFinder(winrt::hstring key, bool match_case, bool whole_word, bool skip_blanks);
        bool ImportAnnot(RDRect rect, array_view<uint8_t const> buf, int buf_len)
        {
            return Page_importAnnot(m_page, (PDF_RECT*)&rect, buf.data(), buf_len);
        }
        int ObjsAlignWord(int index, int dir)
        {
            return Page_objsAlignWord(m_page, index, dir);
        }
        int ObjsGetCharCount()
        {
            return Page_objsGetCharCount(m_page);
        }
        winrt::hstring ObjsGetCharFontName(int index)
        {
            return cvt_cstr_str(Page_objsGetCharFontName(m_page, index));
        }
        int ObjsGetCharIndex(float x, float y)
        {
            return Page_objsGetCharIndex(m_page, x, y);
        }
        RDRect ObjsGetCharRect(int index)
        {
            RDRect rect;
            Page_objsGetCharRect(m_page, index, (PDF_RECT*)&rect);
            return rect;
        }
        winrt::hstring ObjsGetString(int from, int to)
        {
            wchar_t* txt = (wchar_t*)malloc(sizeof(wchar_t) * (to - from + 3));
            Page_objsGetStringW(m_page, from, to, txt, to - from + 2);
            winrt::hstring ret = txt;
            free(txt);
            return ret;
        }
        void ObjsStart()
        {
            Page_objsStart(m_page);
        }
        bool Reflow(RDDIB dib, float orgx, float orgy)
        {
            return Page_reflow(m_page, (PDF_DIB)dib.Handle(), orgx, orgy);
        }
        float ReflowStart(float width, float ratio, bool reflow_images)
        {
            return Page_reflowStart(m_page, width, ratio, reflow_images);
        }
        bool ReflowToBmp(RDSoftBmp bmp, float orgx, float orgy)
        {
            return Page_reflowToBmp(m_page, (PDF_BMP)bmp.Handle(), orgx, orgy);
        }
        bool Render(RDDIB dib, RDMatrix mat, bool show_annot, RD_RENDER_MODE mode)
        {
            return Page_render(m_page, (PDF_DIB)dib.Handle(), (PDF_MATRIX)mat.Handle(), show_annot, (::PDF_RENDER_MODE)mode);
        }
        void RenderCancel()
        {
            Page_renderCancel(m_page);
        }
        bool RenderIsFinished()
        {
            return Page_renderIsFinished(m_page);
        }
        void RenderPrepare()
        {
            Page_renderPrepare(m_page, NULL);
        }
        void RenderPrepare(RDDIB dib)
        {
            Page_renderPrepare(m_page, (PDF_DIB)dib.Handle());
        }
        bool RenderToBmp(RDBmp bmp, RDMatrix mat, bool show_annot, RD_RENDER_MODE mode)
        {
            return Page_renderToBmp(m_page, (PDF_BMP)bmp.Handle(), (PDF_MATRIX)mat.Handle(), show_annot, (::PDF_RENDER_MODE)mode);
        }
        bool RenderToSoftBmp(RDSoftBmp bmp, RDMatrix mat, bool show_annot, RD_RENDER_MODE mode)
        {
            return Page_renderToBmp(m_page, (PDF_BMP)bmp.Handle(), (PDF_MATRIX)mat.Handle(), show_annot, (::PDF_RENDER_MODE)mode);
        }
        int Sign(PDFDocForm form, RDRect rect, winrt::hstring cert_file, winrt::hstring pswd, winrt::hstring name, winrt::hstring reason, winrt::hstring location, winrt::hstring contact)
        {
            char* ccert_file = cvt_str_cstr(cert_file);
            char* cpswd = cvt_str_cstr(pswd);
            char* cname = cvt_str_cstr(name);
            char* creason = cvt_str_cstr(reason);
            char* clocation = cvt_str_cstr(location);
            char* ccontact = cvt_str_cstr(contact);
            int ret = Page_sign(m_page, (PDF_DOC_FORM)form.Handle(), (const PDF_RECT*)&rect, ccert_file, cpswd, cname, creason, clocation, ccontact);
            free(ccontact);
            free(clocation);
            free(creason);
            free(cname);
            free(cpswd);
            free(ccert_file);
            return ret;
        }
    private:
        PDF_PAGE m_page;
    };
}

namespace winrt::RDUILib::factory_implementation
{
    struct PDFPage : PDFPageT<PDFPage, implementation::PDFPage>
    {
    };
}
