///////////////////////////////////////////////////////////////////////////////
// Name:        pdftemplate.h
// Purpose:
// Author:      Ulrich Telle
// Created:     2006-07-13
// Copyright:   (c) Ulrich Telle
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

/// \file pdftemplate.h Interface of the wxPdfTemplate class

#ifndef _PDF_TEMPLATE_H_
#define _PDF_TEMPLATE_H_

// wxWidgets headers
#include <wx/mstream.h>

// wxPdfDocument headers
#include "wx/pdfdocdef.h"
#include "wx/pdfdocument.h"

class WXDLLIMPEXP_FWD_PDFDOC wxPdfDocument;
class WXDLLIMPEXP_FWD_PDFDOC wxPdfObject;
class WXDLLIMPEXP_FWD_PDFDOC wxPdfParser;
class WXDLLIMPEXP_FWD_PDFDOC wxPdfTemplate;

/// Class representing a template (For internal use only)
class WXDLLIMPEXP_PDFDOC wxPdfTemplate
{
public:
  /// Constructor
  /**
  * \param templateId The template index
  */
  wxPdfTemplate(int templateId);

  /// Destructor
  virtual ~wxPdfTemplate();

  /// Get index of the template
  /**
  * \return The template index
  */
  int    GetIndex()  { return m_templateId; }

  /// Get X position of template
  /**
  * \return The X position
  */
  double GetX()      { return m_x; }

  /// Get Y position of template
  /**
  * \return The Y position
  */
  double GetY()      { return m_y; }

  /// Get width of template
  /**
  * \return The template width
  */
  double GetWidth()  { return m_w; }

  /// Get height of template
  /**
  * \return The template height
  */
  double GetHeight() { return m_h; }

  /// Set object index
  /**
  * \param n The object index
  */
  void SetObjIndex(int n) { m_n = n; }

  /// Get object index
  /**
  * \return The object index
  */
  int  GetObjIndex() { return m_n; }

  /// Set the associated parser
  /**
  * \param parser The parser associated with the template
  */
  void SetParser(wxPdfParser* parser) { m_parser = parser; }

  /// Get the associated parser
  /**
  * \return The associated parser
  */
  wxPdfParser* GetParser() { return m_parser; }

  /// Set the array of page resource objects
  /**
  * \param resources The page resource objects
  */
  void SetResources(wxPdfObject* resources) { m_resources = resources; }

  /// Get the array of page resource objects
  /**
  * \return The page resource objects
  */
  wxPdfObject* GetResources() { return m_resources; }

private:
  int                  m_templateId;        ///< Index of template
  int                  m_n;                 ///< Object number of template
  bool                 m_used;              ///< Flag whether the template has been used

  double               m_x;                 ///< X position of template
  double               m_y;                 ///< Y position of template
  double               m_h;                 ///< Height of template
  double               m_w;                 ///< Width of template

  wxPdfFontHashMap*    m_fonts;             ///< array of used fonts
  wxPdfImageHashMap*   m_images;            ///< array of used images
  wxPdfTemplatesMap*   m_templates;         ///< array of templates
  wxPdfExtGStateMap*   m_extGStates;        ///< array of extended graphics states
  wxPdfPatternMap*     m_patterns;          ///< array of patterns

  wxPdfParser*         m_parser;            ///< Associated parser
  wxPdfObject*         m_resources;         ///< Array of page resource objects

  int                  m_stateSave;         ///< Saved document state
  double               m_xSave;             ///< Saved X position
  double               m_ySave;             ///< Saved Y position
  bool                 m_autoPageBreakSave; ///< State of auto page break
  double               m_bMarginSave;       ///< Saved bottom margin
  double               m_tMarginSave;       ///< Saved top margin
  double               m_lMarginSave;       ///< Saved left margin
  double               m_rMarginSave;       ///< Saved right margin
  double               m_hSave;             ///< Saved height
  double               m_wSave;             ///< Saved width

  wxMemoryOutputStream m_buffer;            ///< Buffer holding in-memory PDF

  friend class wxPdfDocument;
};

#endif

