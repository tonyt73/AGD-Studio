object frmAdvancedSettings: TfrmAdvancedSettings
  Left = 0
  Top = 0
  Caption = 'Settings'
  ClientHeight = 752
  ClientWidth = 725
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object panButtons: TPanel
    Left = 0
    Top = 704
    Width = 725
    Height = 48
    Align = alBottom
    BevelOuter = bvNone
    ShowCaption = False
    TabOrder = 0
  end
  object crdPanels: TCardPanel
    Left = 273
    Top = 0
    Width = 452
    Height = 704
    Align = alClient
    ActiveCard = Card2
    BevelOuter = bvNone
    TabOrder = 1
    object Card1: TCard
      Left = 0
      Top = 0
      Width = 452
      Height = 704
      Caption = 'Card1'
      CardIndex = 0
      TabOrder = 0
    end
    object Card2: TCard
      Left = 0
      Top = 0
      Width = 452
      Height = 704
      Caption = 'Card2'
      CardIndex = 1
      TabOrder = 1
    end
  end
  object TreeView1: TTreeView
    Left = 0
    Top = 0
    Width = 273
    Height = 704
    Align = alLeft
    Indent = 19
    TabOrder = 2
  end
end
