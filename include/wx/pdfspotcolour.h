///////////////////////////////////////////////////////////////////////////////
// Name:        pdfspotcolour.h
// Purpose:
// Author:      Ulrich Telle
// Created:     2009-05-25
// Copyright:   (c) Ulrich Telle
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

/// \file pdfspotcolour.h Interface of the spot colour class

#ifndef _PDF_SPOT_COLOUR_H_
#define _PDF_SPOT_COLOUR_H_

// wxWidgets headers

// wxPdfDocument headers
#include "wx/pdfdocdef.h"

/// Class representing spot colours.
class WXDLLIMPEXP_PDFDOC wxPdfSpotColour
{
public:
  /// Constructor for spot colour
  /**
  * \param index The spot colour index
  * \param cyan The cyan component (0.0 to 100.0)
  * \param magenta The magenta component (0.0 to 100.0)
  * \param yellow The yellow component (0.0 to 100.0)
  * \param black The black component (0.0 to 100.0)
  */
  wxPdfSpotColour(int index, double cyan, double magenta, double yellow, double black);

  /// Copy constructor
  /**
  * \param colour The spot colour to copy
  */
  wxPdfSpotColour(const wxPdfSpotColour& colour);

  /// Set object index
  /**
  * \param index The object index
  */
  void SetObjIndex(int index) { m_objIndex = index; }

  /// Get object index
  /**
  * \return The object index
  */
  int GetObjIndex() const { return m_objIndex; }

  /// Get spot colour index
  /**
  * \return The spot colour index
  */
  int GetIndex() const { return m_index; }

  /// Get cyan level
  /**
  * \return The cyan component
  */
  double GetCyan() const { return m_cyan; }

  /// Get magenta level
  /**
  * \return The magenta component
  */
  double GetMagenta() const { return m_magenta; }

  /// Get yellow level
  /**
  * \return The yellow component
  */
  double GetYellow() const { return m_yellow; }

  /// Get black level
  /**
  * \return The black component
  */
  double GetBlack() const { return m_black; }

private:
  int    m_objIndex;   ///< object index
  int    m_index;      ///< colour index
  double m_cyan;       ///< cyan level
  double m_magenta;    ///< magenta level
  double m_yellow;     ///< yellow level
  double m_black;      ///< black level
};

#endif
