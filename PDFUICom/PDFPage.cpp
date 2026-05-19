#include "pch.h"
#include "PDFPage.h"
#include "RDUILib.PDFPage.g.cpp"
#include "PDFDocFont.h"
#include "PDFResFont.h"
#include "PDFDocForm.h"
#include "PDFResForm.h"
#include "PDFDocGState.h"
#include "PDFResGState.h"
#include "PDFDocImage.h"
#include "PDFResImage.h"
#include "PDFAnnot.h"
#include "PDFFinder.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::RDUILib::implementation
{
    RDUILib::PDFResFont PDFPage::AddResFont(RDUILib::PDFDocFont font)
    {
        int64_t pf = (int64_t)Page_addResFont(m_page, (PDF_DOC_FONT)font.Handle());
        return (pf) ? winrt::make<implementation::PDFResFont>(pf) : nullptr;
    }
    RDUILib::PDFResForm PDFPage::AddResForm(RDUILib::PDFDocForm form)
    {
        int64_t pf = (int64_t)Page_addResForm(m_page, (PDF_DOC_FORM)form.Handle());
        return (pf) ? winrt::make<implementation::PDFResForm>(pf) : nullptr;
    }
    RDUILib::PDFResGState PDFPage::AddResGState(RDUILib::PDFDocGState gs)
    {
        int64_t pf = (int64_t)Page_addResGState(m_page, (PDF_DOC_GSTATE)gs.Handle());
        return (pf) ? winrt::make<implementation::PDFResGState>(pf) : nullptr;
    }
    RDUILib::PDFResImage PDFPage::AddResImage(RDUILib::PDFDocImage image)
    {
        int64_t pf = (int64_t)Page_addResImage(m_page, (PDF_DOC_IMAGE)image.Handle());
        return (pf) ? winrt::make<implementation::PDFResImage>(pf) : nullptr;
    }
    RDUILib::PDFAnnot PDFPage::GetAnnot(float x, float y)
    {
        PDF_ANNOT annot = Page_getAnnotFromPoint(m_page, x, y);
        if (annot) return winrt::make<implementation::PDFAnnot>((int64_t)m_page, (int64_t)annot);
        else return nullptr;
    }
    RDUILib::PDFAnnot PDFPage::GetAnnot(int index)
    {
        PDF_ANNOT annot = Page_getAnnot(m_page, index);
        if (annot) return winrt::make<implementation::PDFAnnot>((int64_t)m_page, (int64_t)annot);
        else return nullptr;
    }
    RDUILib::PDFFinder PDFPage::GetFinder(winrt::hstring key, bool match_case, bool whole_word)
    {
        PDF_FINDER find = Page_findOpenW(m_page, key.c_str(), match_case, whole_word);
        if (find) return winrt::make<implementation::PDFFinder>((int64_t)find);
        else return nullptr;
    }
    RDUILib::PDFFinder PDFPage::GetFinder(winrt::hstring key, bool match_case, bool whole_word, bool skip_blanks)
    {
        PDF_FINDER find = Page_findOpen2W(m_page, key.c_str(), match_case, whole_word, skip_blanks);
        if (find) return winrt::make<implementation::PDFFinder>((int64_t)find);
        else return nullptr;
    }
}
