object frmNewImage: TfrmNewImage
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'New Image'
  ClientHeight = 142
  ClientWidth = 343
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Roboto'
  Font.Style = []
  Position = poMainFormCenter
  ScreenSnap = True
  OnCreate = FormCreate
  DesignSize = (
    343
    142)
  TextHeight = 15
  object lblWidth: TLabel
    Left = 16
    Top = 64
    Width = 37
    Height = 17
    Caption = 'Width'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Roboto'
    Font.Style = []
    ParentFont = False
  end
  object lblHeight: TLabel
    Left = 205
    Top = 64
    Width = 42
    Height = 17
    Anchors = [akTop, akRight]
    Caption = 'Height'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Roboto'
    Font.Style = []
    ParentFont = False
    ExplicitLeft = 211
  end
  object Panel1: TPanel
    Left = 0
    Top = 102
    Width = 343
    Height = 40
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    TabStop = True
    DesignSize = (
      343
      40)
    object btnOk: TButton
      Left = 172
      Top = 10
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'OK'
      Default = True
      ModalResult = 1
      TabOrder = 0
      ExplicitLeft = 177
    end
    object btnCancel: TButton
      Left = 256
      Top = 10
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Cancel = True
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
      ExplicitLeft = 261
    end
  end
  object edtWidth: TElSpinEdit
    Left = 59
    Top = 60
    Width = 64
    Height = 25
    Cursor = crIBeam
    AllowEdit = False
    UseCustomScrollBars = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Roboto'
    Font.Style = [fsBold]
    Flat = True
    ParentFont = False
    TabOrder = 1
  end
  object edtHeight: TElSpinEdit
    Left = 259
    Top = 60
    Width = 64
    Height = 25
    Cursor = crIBeam
    AllowEdit = False
    ButtonFlat = True
    ButtonOldStyled = True
    UseCustomScrollBars = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Roboto'
    Font.Style = [fsBold]
    Flat = True
    ParentFont = False
    TabOrder = 2
  end
  object tbcImageTypes: TTabControl
    Left = 0
    Top = 0
    Width = 343
    Height = 40
    Align = alTop
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Roboto'
    Font.Style = [fsBold]
    HotTrack = True
    OwnerDraw = True
    ParentFont = False
    TabHeight = 38
    TabOrder = 3
    Tabs.Strings = (
      'OBJECT'
      'SPRITE'
      'TILE')
    TabIndex = 0
    TabWidth = 113
    StyleElements = [seFont, seClient]
    OnChange = tbcImageTypesChange
    OnDrawTab = tbcImageTypesDrawTab
  end
end
