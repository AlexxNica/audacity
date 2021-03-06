/**********************************************************************

  Audacity: A Digital Audio Editor

  TracksBehaviorsPrefs.cpp

  Steve Daulton


*******************************************************************//**

\class TracksBehaviorsPrefs
\brief A PrefsPanel for Tracks Behaviors settings.

*//*******************************************************************/

#include "../Audacity.h"
#include "TracksBehaviorsPrefs.h"

#include "../Prefs.h"
#include "../ShuttleGui.h"
#include "../Experimental.h"

TracksBehaviorsPrefs::TracksBehaviorsPrefs(wxWindow * parent)
:  PrefsPanel(parent, _("Tracks Behaviors"))
{
   Populate();
}

TracksBehaviorsPrefs::~TracksBehaviorsPrefs()
{
}

const wxChar *TracksBehaviorsPrefs::ScrollingPreferenceKey()
{
   static auto string = wxT("/GUI/ScrollBeyondZero");
   return string;
}

void TracksBehaviorsPrefs::Populate()
{
   mSoloCodes.Add(wxT("Simple"));
   mSoloCodes.Add(wxT("Multi"));
   mSoloCodes.Add(wxT("None"));

   mSoloChoices.Add(_("Simple"));
   mSoloChoices.Add(_("Multi-track"));
   mSoloChoices.Add(_("None"));

   //------------------------- Main section --------------------
   // Now construct the GUI itself.
   ShuttleGui S(this, eIsCreatingFromPrefs);
   PopulateOrExchange(S);
   // ----------------------- End of main section --------------
}

void TracksBehaviorsPrefs::PopulateOrExchange(ShuttleGui & S)
{
   S.SetBorder(2);

   S.StartStatic(_("Behaviors"));
   {
      S.TieCheckBox(_("&Select then act on entire project, if no audio selected"),
                    wxT("/GUI/SelectAllOnNone"),
                    true);
      /* i18n-hint: cut-lines are a lines indicating where to cut.*/
      S.TieCheckBox(_("Enable cut &lines"),
                    wxT("/GUI/EnableCutLines"),
                    false);
      S.TieCheckBox(_("Enable &dragging of left and right selection edges"),
                    wxT("/GUI/AdjustSelectionEdges"),
                    true);
      S.TieCheckBox(_("\"Move track focus\" c&ycles repeatedly through tracks"),
                    wxT("/GUI/CircularTrackNavigation"),
                    false);
      S.TieCheckBox(_("Editing a clip can &move other clips"),
                    wxT("/GUI/EditClipCanMove"),
                    true);
      S.TieCheckBox(_("&Type to create a label"),
                    wxT("/GUI/TypeToCreateLabel"),
                    true);
#ifdef EXPERIMENTAL_SCROLLING_LIMITS
      S.TieCheckBox(_("Enable scrolling left of &zero"),
                    ScrollingPreferenceKey(),
                    ScrollingPreferenceDefault());
#endif

      S.AddSpace(10);

      S.StartMultiColumn(2);
      {
         S.TieChoice(_("Solo &Button:"),
                     wxT("/GUI/Solo"),
                     wxT("Standard"),
                     mSoloChoices,
                     mSoloCodes);
         S.SetSizeHints(mSoloChoices);
      }
      S.EndMultiColumn();
   }
   S.EndStatic();
}

bool TracksBehaviorsPrefs::Apply()
{
   ShuttleGui S(this, eIsSavingToPrefs);
   PopulateOrExchange(S);

   return true;
}

TracksBehaviorsPrefsFactory::TracksBehaviorsPrefsFactory()
{
}

PrefsPanel *TracksBehaviorsPrefsFactory::Create(wxWindow *parent)
{
   wxASSERT(parent); // to justify safenew
   return safenew TracksBehaviorsPrefs(parent);
}
