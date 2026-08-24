// Minimal wx/fileconf.h stub — wxFileConfig just deriving from wxConfigBase.
#pragma once
#include "wx/confbase.h"

class wxFileConfig : public wxConfigBase {
public:
    wxFileConfig(const wxString& = wxString(),
                 const wxString& = wxString(),
                 const wxString& = wxString(),
                 const wxString& = wxString(),
                 long = 0) {}
};
