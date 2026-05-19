#pragma once

#include "RDUILib.PDFDoc.g.h"
#include "PDFUI3.h"

namespace winrt::RDUILib::implementation
{
    struct PDFDoc : PDFDocT<PDFDoc>
    {
        PDFDoc()
        {
            m_doc = NULL;
        }
        ~PDFDoc()
        {
            Close();
        }
        int64_t Handle() { return (int64_t)m_doc; }
        static void SetOpenFlag(int32_t flag)
        {
            Document_setOpenFlag(flag);
        }
        int32_t CreatePath(winrt::hstring path);
        int32_t Create(IRandomAccessStream stream);
        int32_t OpenPath(winrt::hstring path, winrt::hstring password);
        int32_t Open(IRandomAccessStream stream, winrt::hstring password);
        int32_t PageCount();
        float GetPageWidth(int32_t pageno);
        float GetPageHeight(int32_t pageno);
        winrt::RDUILib::PDFPage GetPage(int32_t pageno);
        void Close();
        winrt::RDUILib::PDFOutline GetRootOutline();
        bool AddRootOutline(winrt::hstring label, int dest, float y);
        int32_t Permission();
        winrt::hstring XMP();
        int32_t Perm();
        int32_t EFCount();
        winrt::hstring GetEFDesc(int32_t index);
        winrt::hstring GetEFName(int32_t index);
        bool GetEFData(int32_t index, winrt::hstring path);
        int32_t JSCount();
        winrt::hstring GetJS(int32_t index);
        winrt::hstring GetJSName(int32_t index);
        bool CanSave();
        bool IsEncrypted();
        bool IsOpened();
        int32_t VerifySign(winrt::RDUILib::PDFSign sign);
        winrt::RDUILib::PDFPage NewPage(int32_t pageno, float w, float h);
        bool RemovePage(int32_t pageno);
        bool MovePage(int32_t srcno, int32_t dstno);

        winrt::RDUILib::PDFImportor ImportStart(winrt::RDUILib::PDFDoc src);
        winrt::RDUILib::PDFDocImage NewImage0(winrt::Microsoft::UI::Xaml::Media::Imaging::WriteableBitmap bitmap, bool has_alpha);
        winrt::RDUILib::PDFDocImage NewImage1(winrt::Windows::Graphics::Imaging::SoftwareBitmap bitmap, bool has_alpha);
        winrt::RDUILib::PDFDocImage NewImage2(winrt::Microsoft::UI::Xaml::Media::Imaging::WriteableBitmap bitmap, int32_t matte);
        winrt::RDUILib::PDFDocImage NewImage3(winrt::Windows::Graphics::Imaging::SoftwareBitmap bitmap, int32_t matte);
        winrt::RDUILib::PDFDocImage NewImageJPEG(winrt::hstring path);
        winrt::RDUILib::PDFDocImage NewImageJPX(winrt::hstring path);
        winrt::RDUILib::PDFDocFont NewFontCID(winrt::hstring name, int32_t style);
        winrt::RDUILib::PDFDocGState NewGState();
        winrt::RDUILib::PDFDocForm NewForm();
        bool SaveAs(winrt::hstring path)
        {
            return Document_saveAsW(m_doc, path.c_str());
        }
        bool Save()
        {
            return Document_save(m_doc);
        }
        bool SetMeta(winrt::hstring tag, winrt::hstring val)
        {
            char* ctag = cvt_str_cstr(tag);
            bool ret = Document_setMeta(m_doc, ctag, val.c_str());
            free(ctag);
            return ret;
        }
        bool SetPageRotate(int32_t pageno, int32_t degree)
        {
            return Document_setPageRotate(m_doc, pageno, degree);
        }
        RDPoint MaxPageSize()
        {
            PDF_POINT pt = Document_getPagesMaxSize(m_doc);
			return *(RDPoint *)&pt;
        }
    private:
        PDF_DOC m_doc;
    };
}

namespace winrt::RDUILib::factory_implementation
{
    struct PDFDoc : PDFDocT<PDFDoc, implementation::PDFDoc>
    {
    };
}
