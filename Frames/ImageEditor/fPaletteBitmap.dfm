object frmPaletteBitmap: TfrmPaletteBitmap
  Left = 0
  Top = 0
  Width = 176
  Height = 105
  Constraints.MaxWidth = 176
  Constraints.MinHeight = 105
  Constraints.MinWidth = 176
  Padding.Left = 8
  Padding.Top = 8
  Padding.Right = 8
  Padding.Bottom = 8
  TabOrder = 0
  DesignSize = (
    176
    105)
  object Image1: TImage
    Left = 8
    Top = 64
    Width = 160
    Height = 32
    Anchors = [akLeft, akTop, akRight, akBottom]
    ExplicitHeight = 44
  end
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 48
    Height = 48
    BevelOuter = bvLowered
    Caption = 'L'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 120
    Top = 8
    Width = 48
    Height = 48
    BevelOuter = bvLowered
    Caption = 'R'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
  end
  object Button1: TButton
    Left = 64
    Top = 15
    Width = 46
    Height = 34
    Caption = 'Swap'
    TabOrder = 2
  end
end
