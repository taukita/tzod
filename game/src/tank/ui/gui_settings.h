// gui_settings.h

#pragma once

#include "ui/Base.h"
#include "ui/Dialog.h"


// forward declaration
class ConfVarTable;


namespace UI
{
///////////////////////////////////////////////////////////////////////////////

class SettingsDlg : public Dialog
{
	List      *_profiles;
	Button    *_editProfile;
	Button    *_deleteProfile;

	CheckBox  *_particles;
	CheckBox  *_showFps;
	CheckBox  *_showTime;
	CheckBox  *_showDamage;
	CheckBox  *_showNames;
	CheckBox  *_askDisplaySettings;

	ScrollBarHorizontal *_volumeSfx;
	int _initialVolumeSfx;

	ScrollBarHorizontal *_volumeMusic;
	int _initialVolumeMusic;


public:
	SettingsDlg(Window *parent);
	virtual ~SettingsDlg();

protected:
	void OnVolumeSfx(float pos);
	void OnVolumeMusic(float pos);

	void OnAddProfile();
	void OnEditProfile();
	void OnDeleteProfile();
	void OnSelectProfile(int index);

	void OnOK();
	void OnCancel();

	void UpdateProfilesList();
	void OnProfileEditorClosed(int code);
};

///////////////////////////////////////////////////////////////////////////////

class ControlProfileDlg : public Dialog
{
	Edit         *_nameEdit;
	List         *_actions;
	CheckBox     *_aimToMouse;
	CheckBox     *_moveToMouse;
	ConfVarTable *_profile;
	string_t      _name;

	float _time;
	int   _activeIndex;
	bool  _skip;
	void OnSelectAction(int index);

public:
	ControlProfileDlg(Window *parent, const char *profileName);
	~ControlProfileDlg();

protected:
	void AddAction(const char *rawname, const string_t &display);

	void OnOK();
	void OnCancel();

	void OnTimeStep(float dt);
	bool OnRawChar(int c);
};

///////////////////////////////////////////////////////////////////////////////

class MapSettingsDlg : public Dialog
{
	Edit *_author;
	Edit *_email;
	Edit *_url;
	Edit *_desc;
	Edit *_onInit;
	ComboBox *_theme;

public:
	MapSettingsDlg(Window *parent);
	~MapSettingsDlg();

	void OnOK();
	void OnCancel();
};

///////////////////////////////////////////////////////////////////////////////
} // end of namespace UI

// end of file
