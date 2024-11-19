object frmNewImage: TfrmNewImage
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'New Image'
  ClientHeight = 142
  ClientWidth = 349
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
    349
    142)
  TextHeight = 15
  object lblWidth: TLabel
    Left = 16
    Top = 67
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
    Left = 211
    Top = 65
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
  end
  object Panel1: TPanel
    Left = 0
    Top = 105
    Width = 349
    Height = 37
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      349
      37)
    object btnOk: TButton
      Left = 178
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'OK'
      Default = True
      ModalResult = 1
      TabOrder = 0
    end
    object btnCancel: TButton
      Left = 262
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Cancel = True
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
    end
  end
  object radObject: TRadioButton
    Left = 16
    Top = 24
    Width = 81
    Height = 17
    Caption = 'Object'
    Checked = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Roboto'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    TabStop = True
    OnClick = radObjectClick
  end
  object radSprite: TRadioButton
    Tag = 1
    Left = 103
    Top = 24
    Width = 66
    Height = 17
    Caption = 'Sprite'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Roboto'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = radObjectClick
  end
  object radTile: TRadioButton
    Tag = 2
    Left = 187
    Top = 24
    Width = 66
    Height = 17
    Caption = 'Tile'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Roboto'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = radObjectClick
  end
  object edtHeight: TSpinEdit
    Left = 264
    Top = 61
    Width = 73
    Height = 27
    Anchors = [akTop, akRight]
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Roboto'
    Font.Style = []
    Increment = 8
    MaxValue = 128
    MinValue = 8
    ParentFont = False
    TabOrder = 5
    Value = 16
    OnExit = edtHeightExit
  end
  object radChrSet: TRadioButton
    Tag = 3
    Left = 267
    Top = 24
    Width = 82
    Height = 17
    Caption = 'Char Set'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Roboto'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = radObjectClick
  end
  object edtWidth: TSpinEdit
    Left = 68
    Top = 61
    Width = 73
    Height = 27
    Anchors = [akTop, akRight]
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -14
    Font.Name = 'Roboto'
    Font.Style = []
    Increment = 8
    MaxValue = 128
    MinValue = 8
    ParentFont = False
    TabOrder = 6
    Value = 16
    OnExit = edtWidthExit
  end
end
