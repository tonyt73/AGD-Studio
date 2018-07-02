object frmBlockTypes: TfrmBlockTypes
  Left = 0
  Top = 0
  Width = 176
  Height = 306
  TabOrder = 0
  object btnPlatform: TSpeedButton
    Tag = 1
    Left = 40
    Top = 64
    Width = 128
    Height = 32
    AllowAllUp = True
    GroupIndex = 1
    Caption = 'Platform'
    OnClick = btnPlatformClick
  end
  object btnWall: TSpeedButton
    Tag = 2
    Left = 40
    Top = 104
    Width = 128
    Height = 32
    AllowAllUp = True
    GroupIndex = 1
    Caption = 'Wall'
    OnClick = btnPlatformClick
  end
  object btnLadder: TSpeedButton
    Tag = 3
    Left = 40
    Top = 144
    Width = 128
    Height = 32
    AllowAllUp = True
    GroupIndex = 1
    Caption = 'Ladder'
    OnClick = btnPlatformClick
  end
  object btnFodder: TSpeedButton
    Tag = 4
    Left = 40
    Top = 184
    Width = 128
    Height = 32
    AllowAllUp = True
    GroupIndex = 1
    Caption = 'Fodder'
    OnClick = btnPlatformClick
  end
  object btnDeadly: TSpeedButton
    Tag = 5
    Left = 40
    Top = 226
    Width = 133
    Height = 32
    AllowAllUp = True
    GroupIndex = 1
    Caption = 'Deadly'
    OnClick = btnPlatformClick
  end
  object btnCustom: TSpeedButton
    Tag = 6
    Left = 40
    Top = 264
    Width = 128
    Height = 32
    AllowAllUp = True
    GroupIndex = 1
    Caption = 'Custom'
    OnClick = btnPlatformClick
  end
  object Shape1: TShape
    Left = 8
    Top = 65
    Width = 31
    Height = 30
    Brush.Color = clBlue
  end
  object Shape2: TShape
    Left = 8
    Top = 105
    Width = 31
    Height = 30
    Brush.Color = 27391
  end
  object Shape3: TShape
    Left = 8
    Top = 145
    Width = 31
    Height = 30
    Brush.Color = clLime
  end
  object Shape4: TShape
    Left = 8
    Top = 185
    Width = 31
    Height = 30
    Brush.Color = 14418175
  end
  object Shape5: TShape
    Left = 8
    Top = 228
    Width = 31
    Height = 30
    Brush.Color = clRed
  end
  object Shape6: TShape
    Left = 8
    Top = 265
    Width = 31
    Height = 30
  end
  object panBlock: TPanel
    Left = 8
    Top = 8
    Width = 48
    Height = 48
    Hint = 'The current Block type'
    BevelOuter = bvLowered
    Caption = 'P'
    Color = clBlue
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    StyleElements = [seBorder]
  end
  object panEmpty: TPanel
    Left = 120
    Top = 8
    Width = 48
    Height = 48
    Hint = 'Right mouse sets (clears) block type to Empty'
    BevelOuter = bvLowered
    Caption = 'E'
    Color = clBlue
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
  end
end
