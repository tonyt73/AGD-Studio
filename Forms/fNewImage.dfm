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
    Top = 64
    Width = 32
    Height = 15
    Caption = 'Width'
    Enabled = False
  end
  object lblHeight: TLabel
    Left = 212
    Top = 64
    Width = 37
    Height = 15
    Anchors = [akTop, akRight]
    Caption = 'Height'
    Enabled = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 105
    Width = 349
    Height = 37
    Align = alBottom
    BevelOuter = bvNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    DesignSize = (
      349
      37)
    object btnOk: TButton
      Left = 182
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
      Left = 266
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
    Left = 72
    Top = 24
    Width = 57
    Height = 17
    Caption = 'Object'
    Checked = True
    TabOrder = 1
    TabStop = True
    OnClick = radObjectClick
  end
  object radSprite: TRadioButton
    Tag = 1
    Left = 139
    Top = 24
    Width = 58
    Height = 17
    Caption = 'Sprite'
    TabOrder = 2
    OnClick = radObjectClick
  end
  object radTile: TRadioButton
    Tag = 2
    Left = 211
    Top = 24
    Width = 40
    Height = 17
    Caption = 'Tile'
    TabOrder = 3
    OnClick = radObjectClick
  end
  object edtHeight: TSpinEdit
    Left = 268
    Top = 61
    Width = 73
    Height = 24
    Anchors = [akTop, akRight]
    Enabled = False
    Increment = 8
    MaxValue = 128
    MinValue = 8
    TabOrder = 5
    Value = 16
    OnExit = edtHeightExit
  end
  object radChrSet: TRadioButton
    Tag = 3
    Left = 268
    Top = 24
    Width = 73
    Height = 17
    Caption = 'Char Set'
    TabOrder = 4
    OnClick = radObjectClick
  end
  object edtWidth: TSpinEdit
    Left = 72
    Top = 61
    Width = 73
    Height = 24
    Anchors = [akTop, akRight]
    Enabled = False
    Increment = 8
    MaxValue = 128
    MinValue = 8
    TabOrder = 6
    Value = 16
    OnExit = edtWidthExit
  end
end
