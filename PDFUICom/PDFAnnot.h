#pragma once

#include "RDUILib.PDFAnnot.g.h"
#include "PDFUI3.h"
char* cvt_str_cstr(winrt::hstring str);
winrt::hstring cvt_cstr_str(const char* str);

namespace winrt::RDUILib::implementation
{
    struct PDFAnnot : PDFAnnotT<PDFAnnot>
    {
        PDFAnnot(int64_t page, int64_t hand)
        {
            m_page = (PDF_PAGE)page;
            m_hand = (PDF_ANNOT)hand;
        }
        int64_t Handle() { return (int64_t)m_hand; }
        bool DoReset()
        {
            return Page_setAnnotReset(m_page, m_hand);
        }
        com_array<uint8_t> Export()
        {
            unsigned char* buf = (unsigned char*)malloc(8192);
            int len = Page_exportAnnot(m_page, m_hand, buf, 8192);
            com_array<uint8_t> ret(len);
            memcpy(ret.data(), buf, len);
            free(buf);
            return ret;
        }
        bool FlateFromPage()
        {
            bool ret = Page_flateAnnot(m_page, m_hand);
            if (ret)
            {
                m_page = NULL;
                m_hand = NULL;
            }
            return ret;
        }
        bool Get3DData(winrt::hstring save_path)
        {
            char* tmp = cvt_str_cstr(save_path);
            bool ret = Page_getAnnot3DData(m_page, m_hand, tmp);
            free(tmp);
            return ret;
        }
        winrt::hstring Get3DName()
        {
            return Page_getAnnot3D(m_page, m_hand);
        }
        bool GetAttachmentData(winrt::hstring save_path)
        {
            char* tmp = cvt_str_cstr(save_path);
            bool ret = Page_getAnnotAttachmentData(m_page, m_hand, tmp);
            free(tmp);
            return ret;
        }
        winrt::hstring GetAttachmentName()
        {
            return Page_getAnnotAttachment(m_page, m_hand);
        }
        int GetCheckStatus()
        {
            return Page_getAnnotCheckStatus(m_page, m_hand);
        }
        winrt::hstring GetComboItem(int item)
        {
            return Page_getAnnotComboItem(m_page, m_hand, item);
        }
        winrt::hstring GetFieldJS(int idx)
        {
            return Page_getAnnotFieldJS(m_page, m_hand, idx);
        }
        RDPoint GetLinePoint(int index)
        {
            PDF_POINT pt;
            pt.x = 0;
            pt.y = 0;
            Page_getAnnotLinePoint(m_page, m_hand, index, &pt);
            return *(RDPoint*)&pt;
        }
        winrt::hstring GetListItem(int item)
        {
            return Page_getAnnotListItem(m_page, m_hand, item);
        }
        bool GetMovieData(winrt::hstring save_path)
        {
            char* tmp = cvt_str_cstr(save_path);
            bool ret = Page_getAnnotMovieData(m_page, m_hand, tmp);
            free(tmp);
            return ret;
        }
        winrt::hstring GetMovieName()
        {
            return Page_getAnnotMovie(m_page, m_hand);
        }
        bool GetRenditionData(winrt::hstring save_path)
        {
            char* tmp = cvt_str_cstr(save_path);
            bool ret = Page_getAnnotRenditionData(m_page, m_hand, tmp);
            free(tmp);
            return ret;
        }
        winrt::hstring GetRenditionName()
        {
            return Page_getAnnotRendition(m_page, m_hand);
        }
        RDUILib::PDFAnnot GetReply(int idx)
        {
            PDF_ANNOT annot = Page_getAnnotReply(m_page, m_hand, idx);
            if (!annot) return nullptr;
            return winrt::make<implementation::PDFAnnot>((int64_t)m_page, (int64_t)m_hand);
        }
        bool GetRichMediaData(winrt::hstring name, winrt::hstring save_path)
        {
            return Page_getAnnotRichMediaData(m_page, m_hand, name, save_path);
        }
        winrt::hstring GetRichMediaItemAsset(int idx)
        {
            return Page_getAnnotRichMediaItemAsset(m_page, m_hand, idx);
        }
        winrt::hstring GetRichMediaItemPara(int idx)
        {
            return Page_getAnnotRichMediaItemPara(m_page, m_hand, idx);
        }
        winrt::hstring GetRichMediaItemSource(int idx)
        {
            return Page_getAnnotRichMediaItemSource(m_page, m_hand, idx);
        }
        bool GetRichMediaItemSourceData(int idx, winrt::hstring save_path)
        {
            return Page_getAnnotRichMediaItemSourceData(m_page, m_hand, idx, save_path);
        }
        int GetRichMediaItemType(int idx)
        {
            return Page_getAnnotRichMediaItemType(m_page, m_hand, idx);
        }
        com_array<int> GetSoundData(winrt::hstring save_path)
        {
            int paras[6];
            char* tmp = cvt_str_cstr(save_path);
            bool ret = Page_getAnnotSoundData(m_page, m_hand, paras, tmp);
            free(tmp);
            if (!ret) return com_array<int>(0);
            else
            {
                com_array<int> arr(6);
                memcpy(arr.data(), paras, sizeof(int) * 6);
                return arr;
            }
        }
        winrt::hstring GetSoundName()
        {
            return Page_getAnnotSound(m_page, m_hand);
        }
        bool IsResetButton()
        {
            return Page_getAnnotReset(m_page, m_hand);
        }
        bool MoveToPage(RDUILib::PDFPage page, RDRect rect)
        {
            if (!m_page) return false;
            return Page_moveAnnot(m_page, (PDF_PAGE)page.Handle(), m_hand, (const PDF_RECT*)&rect);
        }
        bool RemoveFromPage()
        {
            bool ret = Page_removeAnnot(m_page, m_hand);
            if (ret)
            {
                m_page = nullptr;
                m_hand = NULL;
            }
            return ret;
        }
        bool RenderToBmp(RDUILib::RDBmp bmp)
        {
            if (!bmp || !m_page) return false;
            return Page_renderAnnotToBmp(m_page, m_hand, (PDF_BMP)bmp.Handle());
        }
        bool RenderToSoftBmp(RDUILib::RDSoftBmp bmp)
        {
            if (!bmp || !m_page) return false;
            return Page_renderAnnotToBmp(m_page, m_hand, (PDF_BMP)bmp.Handle());
        }
        bool SetCheckValue(bool check)
        {
            return Page_setAnnotCheckValue(m_page, m_hand, check);
        }
        bool SetEditFont(RDUILib::PDFDocFont font)
        {
            if (!font) return false;
            return Page_setAnnotEditFont(m_page, m_hand, (PDF_DOC_FONT)font.Handle());
        }
        bool SetLinePoint(float x1, float y1, float x2, float y2)
        {
            return Page_setAnnotLinePoint(m_page, m_hand, x1, y1, x2, y2);
        }
        bool SetRadio()
        {
            return Page_setAnnotRadio(m_page, m_hand);
        }
        int SignField(RDUILib::PDFDocForm form, winrt::hstring cert_file, winrt::hstring pswd, winrt::hstring name, winrt::hstring reason, winrt::hstring location, winrt::hstring contact)
        {
            char* ccert_file = cvt_str_cstr(cert_file);
            char* cpswd = cvt_str_cstr(pswd);
            char* cname = cvt_str_cstr(name);
            char* creason = cvt_str_cstr(reason);
            char* clocation = cvt_str_cstr(location);
            char* ccontact = cvt_str_cstr(contact);
            int ret = Page_signAnnotField(m_page, m_hand, (PDF_DOC_FORM)form.Handle(), ccert_file, cpswd, cname, creason, clocation, ccontact);
            free(ccontact);
            free(clocation);
            free(creason);
            free(cname);
            free(cpswd);
            free(ccert_file);
            return ret;
        }
        int ComboItemCount()
        {
            return Page_getAnnotComboItemCount(m_page, m_hand);
        }
        int ComboItemSel()
        {
            return Page_getAnnotComboItemSel(m_page, m_hand);
        }
        void ComboItemSel(int item)
        {
            Page_setAnnotComboItem(m_page, m_hand, item);
        }
        int Dest()
        {
            return Page_getAnnotDest(m_page, m_hand);
        }
        winrt::hstring EditText()
        {
            return Page_getAnnotEditText(m_page, m_hand);
        }
        void EditText(winrt::hstring txt)
        {
            bool ret = Page_setAnnotEditTextW(m_page, m_hand, txt.c_str());
            ret = 0;
        }
        int EditTextAlign() { return Page_getAnnotEditTextAlign(m_page, m_hand); }
        void EditTextAlign(int val) { Page_setAnnotEditTextAlign(m_page, m_hand, val); }
        unsigned int EditTextColor() { return Page_getAnnotEditTextColor(m_page, m_hand); }
        void EditTextColor(unsigned int val) { Page_setAnnotEditTextColor(m_page, m_hand, val); }
        RDRect EditTextRect()
        {
            RDRect rect;
            if (!Page_getAnnotEditTextRect(m_page, m_hand, (PDF_RECT*)&rect))
            {
                rect.left = 0;
                rect.top = 0;
                rect.right = 0;
                rect.bottom = 0;
            }
            return rect;
        }
        float EditTextSize() { return Page_getAnnotEditTextSize(m_page, m_hand); }
        void EditTextSize(float val) { Page_setAnnotEditTextSize(m_page, m_hand, val); }
        int EditType() { return Page_getAnnotEditType(m_page, m_hand); }
        winrt::hstring FieldFullName()
        {
            wchar_t tmp[512] = {0};
            if (Page_getAnnotFieldFullNameW(m_page, m_hand, tmp, 511) <= 0) return L"";
            else return tmp;
        }
        winrt::hstring FieldFullName2()
        {
            wchar_t tmp[512] = {0};
            if (Page_getAnnotFieldFullName2W(m_page, m_hand, tmp, 511) <= 0) return L"";
            else return tmp;
        }
        winrt::hstring FieldName()
        {
            wchar_t tmp[512] = {0};
            if (Page_getAnnotFieldNameW(m_page, m_hand, tmp, 511) <= 0) return L"";
            else return tmp;
        }
        winrt::hstring FieldNameWithNO()
        {
            wchar_t tmp[512] = { 0 };
            if (Page_getAnnotFieldNameWithNOW(m_page, m_hand, tmp, 511) <= 0) return L"";
            else return tmp;
        }
        int FieldType() { return Page_getAnnotFieldType(m_page, m_hand); }
        winrt::hstring FileLink()
        {
            return Page_getAnnotFileLink(m_page, m_hand);
        }
        int FillColor() { return Page_getAnnotFillColor(m_page, m_hand); }
        void FillColor(int color) { Page_setAnnotFillColor(m_page, m_hand, color); }
        bool Hide() { return Page_isAnnotHide(m_page, m_hand); }
        void Hide(bool val) { Page_setAnnotHide(m_page, m_hand, val); }
        int Icon() { return Page_getAnnotIcon(m_page, m_hand); }
        void Icon(int icon) { Page_setAnnotIcon(m_page, m_hand, icon); }
        int IndexInPage()
        {
            int cur = 0;
            int cnt = Page_getAnnotCount(m_page);
            while (cur < cnt)
            {
                PDF_ANNOT tmp = Page_getAnnot(m_page, cur);
                if (tmp == m_hand) return cur;
                cur++;
            }
            return -1;
        }
        RDUILib::RDPath InkPath();
        void InkPath(RDUILib::RDPath path)
        {
            Page_setAnnotInkPath(m_page, m_hand, (PDF_PATH)path.Handle());
        }
        bool Is3D()
        {
            winrt::hstring ret = Page_getAnnot3D(m_page, m_hand);
            return (!ret.empty());
        }
        bool IsAttachment()
        {
            winrt::hstring ret = Page_getAnnotAttachment(m_page, m_hand);
            return (!ret.empty());
        }
        bool IsFileLink()
        {
            winrt::hstring ret = Page_getAnnotFileLink(m_page, m_hand);
            return (!ret.empty());
        }
        bool IsMovie()
        {
            winrt::hstring ret = Page_getAnnotMovie(m_page, m_hand);
            return (!ret.empty());
        }
        bool IsPopup()
        {
            winrt::hstring ret = Page_getAnnotPopupSubject(m_page, m_hand);
            return (!ret.empty());
        }
        bool IsRemoteDest()
        {
            winrt::hstring ret = Page_getAnnotRemoteDest(m_page, m_hand);
            return (!ret.empty());
        }
        bool IsSound()
        {
            winrt::hstring ret = Page_getAnnotSound(m_page, m_hand);
            return (!ret.empty());
        }
        bool IsURI()
        {
            winrt::hstring ret = Page_getAnnotURI(m_page, m_hand);
            return (!ret.empty());
        }
        winrt::hstring JS() { return Page_getAnnotJS(m_page, m_hand); }
        int LineStyle() { return Page_getAnnotLineStyle(m_page, m_hand); }
        void LineStyle(int val) { Page_setAnnotLineStyle(m_page, m_hand, val); }
        int ListItemCount() { return Page_getAnnotListItemCount(m_page, m_hand); }
        com_array<int> ListItemSel()
        {
            int sels[128];
            int cnt = Page_getAnnotListSels(m_page, m_hand, sels, 128);
            com_array<int> tmp(cnt);
            memcpy(tmp.data(), sels, cnt * sizeof(int));
            return tmp;
        }
        void ListItemSel(array_view<int const> sel)
        {
            Page_setAnnotListSels(m_page, m_hand, sel.data(), sel.size());
        }
        bool Locked() { return Page_isAnnotLocked(m_page, m_hand); }
        void Locked(bool val) { Page_setAnnotLock(m_page, m_hand, val); }
        bool LockedContent() { return Page_isAnnotLockedContent(m_page, m_hand); }
        RDUILib::RDPath PolygonPath();
        void PolygonPath(RDUILib::RDPath path)
        {
            Page_setAnnotPolygonPath(m_page, m_hand, (PDF_PATH)path.Handle());
        }
        RDUILib::RDPath PolylinePath();
        void PolylinePath(RDUILib::RDPath path)
        {
            Page_setAnnotPolylinePath(m_page, m_hand, (PDF_PATH)path.Handle());
        }
        RDUILib::PDFAnnot Popup()
        {
            PDF_ANNOT pop = Page_getAnnotPopup(m_page, m_hand);
            return (pop) ? winrt::make<implementation::PDFAnnot>((int64_t)m_page, (int64_t)pop) : nullptr;
        }
        winrt::hstring PopupLabel()
        {
            return Page_getAnnotPopupLabel(m_page, m_hand);
        }
        void PopupLabel(winrt::hstring txt)
        {
            Page_setAnnotPopupLabelW(m_page, m_hand, txt.c_str());
        }
        bool PopupOpen()
        {
            return Page_getAnnotPopupOpen(m_page, m_hand);
        }
        void PopupOpen(bool open)
        {
            Page_setAnnotPopupOpen(m_page, m_hand, open);
        }
        winrt::hstring PopupSubject()
        {
            return Page_getAnnotPopupSubject(m_page, m_hand);
        }
        void PopupSubject(winrt::hstring txt)
        {
            Page_setAnnotPopupSubjectW(m_page, m_hand, txt.c_str());
        }
        winrt::hstring PopupText()
        {
            return Page_getAnnotPopupText(m_page, m_hand);
        }
        void PopupText(winrt::hstring txt)
        {
            Page_setAnnotPopupTextW(m_page, m_hand, txt.c_str());
        }
        bool ReadOnly() { return Page_isAnnotReadOnly(m_page, m_hand); }
        void ReadOnly(bool val) { Page_setAnnotReadOnly(m_page, m_hand, val); }
        RDRect Rect() { RDRect rect; Page_getAnnotRect(m_page, m_hand, (PDF_RECT*)&rect); return rect; }
        void Rect(RDRect rect) { Page_setAnnotRect(m_page, m_hand, (const PDF_RECT*)&rect); }
        winrt::hstring RemoteDest()
        {
            return Page_getAnnotRemoteDest(m_page, m_hand);
        }
        int ReplyCount()
        {
            return Page_getAnnotReplyCount(m_page, m_hand);
        }
        int RichMediaItemActived()
        {
            return Page_getAnnotRichMediaItemActived(m_page, m_hand);
        }
        int RichMediaItemCount()
        {
            return Page_getAnnotRichMediaItemCount(m_page, m_hand);
        }
        RDUILib::PDFSign Sign();
        int SignStatus()
        {
            return Page_getAnnotSignStatus(m_page, m_hand);
        }
        int StrokeColor() { return Page_getAnnotStrokeColor(m_page, m_hand); }
        void StrokeColor(int color) { Page_setAnnotStrokeColor(m_page, m_hand, color); }
        com_array<float> StrokeDash() {
            float stmp[128];
            int cnt = Page_getAnnotStrokeDash(m_page, m_hand, stmp, 128);
            if (cnt <= 0) return com_array<float>(0);
            com_array<float> ret(cnt);
            memcpy(ret.data(), stmp, cnt * sizeof(float));
            return ret;
        }
        void StrokeDash(array_view<float const> val)
        {
            Page_setAnnotStrokeDash(m_page, m_hand, val.data(), val.size());
        }
        float StrokeWidth() { return Page_getAnnotStrokeWidth(m_page, m_hand); }
        void StrokeWidth(float val) { Page_setAnnotStrokeWidth(m_page, m_hand, val); }
        winrt::hstring SubmitPara()
        {
            wchar_t uri[512];
            if (!Page_getAnnotSubmitParaW(m_page, m_hand, uri, 511)) return L"";
            else return uri;
        }
        winrt::hstring SubmitTarget()
        {
            return Page_getAnnotSubmitTarget(m_page, m_hand);
        }
        int Type() { return Page_getAnnotType(m_page, m_hand); }
        winrt::hstring URI()
        {
            return Page_getAnnotURI(m_page, m_hand);
        }
        PDF_PAGE m_page;
        PDF_ANNOT m_hand;
    };
}

namespace winrt::RDUILib::factory_implementation
{
    struct PDFAnnot : PDFAnnotT<PDFAnnot, implementation::PDFAnnot>
    {
    };
}
