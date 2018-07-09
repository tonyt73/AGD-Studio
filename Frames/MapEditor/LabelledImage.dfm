object frmLabelledImage: TfrmLabelledImage
  Left = 0
  Top = 0
  Width = 68
  Height = 98
  AutoSize = True
  Constraints.MinHeight = 56
  Color = clBtnFace
  ParentColor = False
  TabOrder = 0
  object panImage: TPanel
    Left = 0
    Top = 0
    Width = 68
    Height = 98
    BevelOuter = bvNone
    Caption = 'panImage'
    Padding.Left = 4
    Padding.Top = 4
    Padding.Right = 4
    Padding.Bottom = 4
    ParentBackground = False
    ShowCaption = False
    TabOrder = 0
    StyleElements = [seFont, seBorder]
    object imgImage: TImage
      Left = 4
      Top = 28
      Width = 60
      Height = 66
      Align = alClient
      Center = True
      Stretch = True
      OnClick = imgImageClick
      ExplicitLeft = 12
      ExplicitTop = 32
      ExplicitWidth = 32
      ExplicitHeight = 64
    end
    object lblCaption: TLabel
      Left = 4
      Top = 4
      Width = 60
      Height = 24
      Align = alTop
      Alignment = taCenter
      AutoSize = False
      Caption = 'lblCaption'
      Layout = tlCenter
      OnClick = imgImageClick
      ExplicitLeft = 2
      ExplicitTop = 2
      ExplicitWidth = 64
    end
  end
end
