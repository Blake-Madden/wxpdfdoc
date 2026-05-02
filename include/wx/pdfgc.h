///////////////////////////////////////////////////////////////////////////////
// Name:        pdfgc.h
// Purpose:     Interface of wxPdfGraphicsContext / wxPdfGraphicsRenderer
// Author:      Ulrich Telle
// Created:     2012-11-25
// Copyright:   (c) Ulrich Telle
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

/// \file pdfgc.h Interface of the wxPdfGraphicsContext and wxPdfGraphicsRenderer classes

#ifndef _PDF_GC_H_
#define _PDF_GC_H_

#include <wx/defs.h>

#if wxUSE_GRAPHICS_CONTEXT

#include <wx/affinematrix2d.h>
#include <wx/cmndata.h>
#include <wx/graphics.h>
#include <wx/vector.h>

#include "wx/pdfdocdef.h"

class WXDLLIMPEXP_FWD_PDFDOC wxPdfDocument;
class WXDLLIMPEXP_FWD_PDFDOC wxPdfDC;

/// wxGraphicsContext that renders into a wxPdfDocument.
///
/// Instances are normally obtained via
/// wxPdfGraphicsRenderer::GetPdfRenderer() or
/// wxPdfDC::GetGraphicsContext(). The rendering primitives mirror the
/// standard wxGraphicsContext API and are translated to wxPdfDocument
/// drawing calls.
class WXDLLIMPEXP_PDFDOC wxPdfGraphicsContext : public wxGraphicsContext
{
public:
  /// Construct a context that owns a freshly-created wxPdfDocument
  /// configured from the given print data.
  wxPdfGraphicsContext(wxGraphicsRenderer* renderer, const wxPrintData& data);

  /// Construct a context that draws into an existing wxPdfDocument as a
  /// template region. The context does not own the document.
  wxPdfGraphicsContext(wxGraphicsRenderer* renderer,
                       wxPdfDocument* pdfDocument,
                       double templateWidth,
                       double templateHeight);

  /// Construct an empty (measuring) context with no associated document.
  wxPdfGraphicsContext(wxGraphicsRenderer* renderer);

  virtual ~wxPdfGraphicsContext();

  // wxGraphicsContext overrides --------------------------------------------

  virtual bool StartDoc(const wxString& message) wxOVERRIDE;
  virtual void EndDoc() wxOVERRIDE;
  virtual void StartPage(wxDouble width = 0, wxDouble height = 0) wxOVERRIDE;
  virtual void EndPage() wxOVERRIDE;

  virtual void PushState() wxOVERRIDE;
  virtual void PopState() wxOVERRIDE;

  virtual void Clip(const wxRegion& region) wxOVERRIDE;
  virtual void Clip(wxDouble x, wxDouble y, wxDouble w, wxDouble h) wxOVERRIDE;
  virtual void ResetClip() wxOVERRIDE;
  virtual void GetClipBox(wxDouble* x, wxDouble* y, wxDouble* w, wxDouble* h) wxOVERRIDE;

  virtual void* GetNativeContext() wxOVERRIDE;

  virtual bool SetAntialiasMode(wxAntialiasMode antialias) wxOVERRIDE;
  virtual bool SetInterpolationQuality(wxInterpolationQuality interpolation) wxOVERRIDE;
  virtual bool SetCompositionMode(wxCompositionMode op) wxOVERRIDE;

  virtual void GetDPI(wxDouble* dpiX, wxDouble* dpiY) const wxOVERRIDE;

  virtual void BeginLayer(wxDouble opacity) wxOVERRIDE;
  virtual void EndLayer() wxOVERRIDE;

  virtual void Translate(wxDouble dx, wxDouble dy) wxOVERRIDE;
  virtual void Scale(wxDouble xScale, wxDouble yScale) wxOVERRIDE;
  virtual void Rotate(wxDouble angle) wxOVERRIDE;
  virtual void ConcatTransform(const wxGraphicsMatrix& matrix) wxOVERRIDE;
  virtual void SetTransform(const wxGraphicsMatrix& matrix) wxOVERRIDE;
  virtual wxGraphicsMatrix GetTransform() const wxOVERRIDE;

  virtual void SetPen(const wxGraphicsPen& pen) wxOVERRIDE;
  virtual void SetBrush(const wxGraphicsBrush& brush) wxOVERRIDE;
  virtual void SetFont(const wxGraphicsFont& font) wxOVERRIDE;

  virtual void StrokePath(const wxGraphicsPath& p) wxOVERRIDE;
  virtual void FillPath(const wxGraphicsPath& p,
                        wxPolygonFillMode fillStyle = wxWINDING_RULE) wxOVERRIDE;
  virtual void DrawPath(const wxGraphicsPath& path,
                        wxPolygonFillMode fillStyle = wxODDEVEN_RULE) wxOVERRIDE;

  virtual void GetTextExtent(const wxString& str,
                             wxDouble* width, wxDouble* height,
                             wxDouble* descent, wxDouble* externalLeading) const wxOVERRIDE;
  virtual void GetPartialTextExtents(const wxString& text,
                                     wxArrayDouble& widths) const wxOVERRIDE;

  virtual void DrawBitmap(const wxGraphicsBitmap& bmp,
                          wxDouble x, wxDouble y,
                          wxDouble w, wxDouble h) wxOVERRIDE;
  virtual void DrawBitmap(const wxBitmap& bmp,
                          wxDouble x, wxDouble y,
                          wxDouble w, wxDouble h) wxOVERRIDE;
  virtual void DrawIcon(const wxIcon& icon,
                        wxDouble x, wxDouble y,
                        wxDouble w, wxDouble h) wxOVERRIDE;

  virtual void StrokeLine(wxDouble x1, wxDouble y1,
                          wxDouble x2, wxDouble y2) wxOVERRIDE;
  virtual void StrokeLines(size_t n, const wxPoint2DDouble* points) wxOVERRIDE;
  virtual void StrokeLines(size_t n,
                           const wxPoint2DDouble* beginPoints,
                           const wxPoint2DDouble* endPoints) wxOVERRIDE;
  virtual void DrawLines(size_t n, const wxPoint2DDouble* points,
                         wxPolygonFillMode fillStyle = wxODDEVEN_RULE) wxOVERRIDE;
  virtual void DrawRectangle(wxDouble x, wxDouble y,
                             wxDouble w, wxDouble h) wxOVERRIDE;
  virtual void DrawEllipse(wxDouble x, wxDouble y,
                           wxDouble w, wxDouble h) wxOVERRIDE;
  virtual void DrawRoundedRectangle(wxDouble x, wxDouble y,
                                    wxDouble w, wxDouble h,
                                    wxDouble radius) wxOVERRIDE;

  virtual bool ShouldOffset() const wxOVERRIDE;

#ifdef __WXMSW__
  // PDF has no native HDC; nothing to hand over.
  virtual WXHDC GetNativeHDC() wxOVERRIDE { return NULL; }
  virtual void ReleaseNativeHDC(WXHDC WXUNUSED(hdc)) wxOVERRIDE {}
#endif

  // PDF-specific accessors --------------------------------------------------

  /// Returns the underlying PDF document. May be NULL until StartDoc().
  wxPdfDocument* GetPdfDocument() { return m_pdfDocument; }

  // Track line / fill alpha so that pen and brush Apply()s can update one
  // side without clobbering the other. Both default to 1.0 (fully opaque).
  // Setting either pushes the combined value to wxPdfDocument::SetAlpha().
  void SetLineAlpha(double a);
  void SetFillAlpha(double a);
  double GetLineAlpha() const { return m_lineAlpha; }
  double GetFillAlpha() const { return m_fillAlpha; }

protected:
  virtual void DoDrawText(const wxString& str, wxDouble x, wxDouble y) wxOVERRIDE;

private:
  void Init();
  void SetPrintData(const wxPrintData& data);

  // Implementation detail used by font metric calculations.
  void CalculateFontMetrics(class wxPdfFontDescription* desc, double pointSize,
                            double* height, double* ascent,
                            double* descent, double* extLeading) const;

  bool           m_templateMode;
  double         m_templateWidth;
  double         m_templateHeight;
  double         m_ppi;
  double         m_ppiPdfFont;
  wxPdfDocument* m_pdfDocument;
  int            m_imageCount;
  wxPrintData    m_printData;
  int            m_mappingModeStyle;

  // Active line / fill opacity (0..1). Pushed to wxPdfDocument::SetAlpha
  // whenever either side changes.
  double         m_lineAlpha;
  double         m_fillAlpha;

  // Shadow of the document's current transformation matrix. PDF cannot
  // read its own CTM back, so we keep one here for GetTransform() and
  // for PushState/PopState restore.
  wxAffineMatrix2D m_ctm;
  wxVector<wxAffineMatrix2D> m_ctmStack;

  // Stack of (lineAlpha, fillAlpha) pairs saved on BeginLayer.
  struct AlphaPair { double line; double fill; };
  wxVector<AlphaPair> m_layerAlphaStack;

  wxDECLARE_NO_COPY_CLASS(wxPdfGraphicsContext);
};

/// Renderer that produces wxPdfGraphicsContext instances.
///
/// Use GetPdfRenderer() to obtain the singleton instance and call
/// CreateContextFromPrintData() or CreateContext(wxPdfDC*) to obtain a
/// concrete context.
class WXDLLIMPEXP_PDFDOC wxPdfGraphicsRenderer : public wxGraphicsRenderer
{
public:
  wxPdfGraphicsRenderer() {}
  virtual ~wxPdfGraphicsRenderer() {}

  /// Returns the process-wide PDF graphics renderer.
  static wxGraphicsRenderer* GetPdfRenderer();

  // PDF-specific factories --------------------------------------------------

  /// Creates a context that owns a freshly-built PDF document configured
  /// from \a printData. Caller takes ownership of the returned context.
  wxGraphicsContext* CreateContextFromPrintData(const wxPrintData& printData);

  /// Creates a context that draws into the document already owned by
  /// \a dc. The returned context does not delete the underlying document
  /// when destroyed; the wxPdfDC retains ownership.
  wxGraphicsContext* CreateContext(wxPdfDC* dc);

  /// Creates a context that draws into the given existing PDF document as
  /// a template region of the given size. The context does not take
  /// ownership of the document.
  wxGraphicsContext* CreateContextFromDocument(wxPdfDocument* pdfDocument,
                                               double templateWidth,
                                               double templateHeight);

  // wxGraphicsRenderer overrides -------------------------------------------

  virtual wxGraphicsContext* CreateContext(const wxWindowDC& dc) wxOVERRIDE;
  virtual wxGraphicsContext* CreateContext(const wxMemoryDC& dc) wxOVERRIDE;
#if wxUSE_PRINTING_ARCHITECTURE
  virtual wxGraphicsContext* CreateContext(const wxPrinterDC& dc) wxOVERRIDE;
#endif
#ifdef __WXMSW__
#if wxUSE_ENH_METAFILE
  virtual wxGraphicsContext* CreateContext(const wxEnhMetaFileDC& dc) wxOVERRIDE;
#endif
#endif

  virtual wxGraphicsContext* CreateContextFromNativeContext(void* context) wxOVERRIDE;
  virtual wxGraphicsContext* CreateContextFromNativeWindow(void* window) wxOVERRIDE;
#ifdef __WXMSW__
  virtual wxGraphicsContext* CreateContextFromNativeHDC(WXHDC dc) wxOVERRIDE;
#endif
  virtual wxGraphicsContext* CreateContext(wxWindow* window) wxOVERRIDE;
#if wxUSE_IMAGE
  virtual wxGraphicsContext* CreateContextFromImage(wxImage& image) wxOVERRIDE;
#endif

  virtual wxGraphicsContext* CreateMeasuringContext() wxOVERRIDE;

  virtual wxGraphicsPath CreatePath() wxOVERRIDE;

  virtual wxGraphicsMatrix CreateMatrix(wxDouble a = 1.0, wxDouble b = 0.0,
                                        wxDouble c = 0.0, wxDouble d = 1.0,
                                        wxDouble tx = 0.0, wxDouble ty = 0.0) wxOVERRIDE;

  virtual wxGraphicsPen CreatePen(const wxGraphicsPenInfo& info) wxOVERRIDE;
  virtual wxGraphicsBrush CreateBrush(const wxBrush& brush) wxOVERRIDE;

  virtual wxGraphicsBrush
  CreateLinearGradientBrush(wxDouble x1, wxDouble y1,
                            wxDouble x2, wxDouble y2,
                            const wxGraphicsGradientStops& stops,
                            const wxGraphicsMatrix& matrix = wxNullGraphicsMatrix) wxOVERRIDE;
  virtual wxGraphicsBrush
  CreateRadialGradientBrush(wxDouble xo, wxDouble yo,
                            wxDouble xc, wxDouble yc,
                            wxDouble radius,
                            const wxGraphicsGradientStops& stops,
                            const wxGraphicsMatrix& matrix = wxNullGraphicsMatrix) wxOVERRIDE;

  virtual wxGraphicsFont CreateFont(const wxFont& font,
                                    const wxColour& col = *wxBLACK) wxOVERRIDE;
  virtual wxGraphicsFont CreateFont(double sizeInPixels,
                                    const wxString& facename,
                                    int flags = wxFONTFLAG_DEFAULT,
                                    const wxColour& col = *wxBLACK) wxOVERRIDE;
  virtual wxGraphicsFont CreateFontAtDPI(const wxFont& font,
                                         const wxRealPoint& dpi,
                                         const wxColour& col = *wxBLACK) wxOVERRIDE;

  virtual wxGraphicsBitmap CreateBitmap(const wxBitmap& bitmap) wxOVERRIDE;
#if wxUSE_IMAGE
  virtual wxGraphicsBitmap CreateBitmapFromImage(const wxImage& image) wxOVERRIDE;
  virtual wxImage CreateImageFromBitmap(const wxGraphicsBitmap& bmp) wxOVERRIDE;
#endif
  virtual wxGraphicsBitmap CreateBitmapFromNativeBitmap(void* bitmap) wxOVERRIDE;
  virtual wxGraphicsBitmap CreateSubBitmap(const wxGraphicsBitmap& bitmap,
                                           wxDouble x, wxDouble y,
                                           wxDouble w, wxDouble h) wxOVERRIDE;

  virtual wxString GetName() const wxOVERRIDE;
  virtual void GetVersion(int* major, int* minor = NULL, int* micro = NULL) const wxOVERRIDE;

private:
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxPdfGraphicsRenderer);
};

#endif // wxUSE_GRAPHICS_CONTEXT

#endif // _PDF_GC_H_
