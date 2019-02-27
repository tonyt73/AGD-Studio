object frmEditorControls: TfrmEditorControls
  AlignWithMargins = True
  Left = 0
  Top = 0
  Width = 1355
  Height = 991
  Padding.Left = 16
  Padding.Top = 8
  Padding.Right = 16
  Padding.Bottom = 16
  TabOrder = 0
  OnMouseActivate = FrameMouseActivate
  DesignSize = (
    1355
    991)
  object Label1: TLabel
    Left = 31
    Top = 7
    Width = 89
    Height = 19
    Caption = ' DIRECTION '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Roboto'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = True
  end
  object Label2: TLabel
    Left = 31
    Top = 183
    Width = 41
    Height = 19
    Caption = ' FIRE '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Roboto'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = True
  end
  object Label3: TLabel
    Left = 31
    Top = 359
    Width = 65
    Height = 19
    Caption = ' OPTION '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Roboto'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = True
  end
  object Line1: TShape
    Left = 16
    Top = 24
    Width = 1320
    Height = 3
    Anchors = [akLeft, akTop, akRight]
    Brush.Color = clBackground
    Pen.Color = clBackground
  end
  object Line2: TShape
    Left = 16
    Top = 200
    Width = 1320
    Height = 3
    Anchors = [akLeft, akTop, akRight]
    Brush.Color = clBackground
    Pen.Color = clBackground
  end
  object Line3: TShape
    Left = 16
    Top = 376
    Width = 1320
    Height = 3
    Anchors = [akLeft, akTop, akRight]
    Brush.Color = clBackground
    Pen.Color = clBackground
  end
  inline kcLeft: TfrmKeyCode
    Left = 31
    Top = 35
    Width = 135
    Height = 130
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    TabOrder = 0
    ExplicitLeft = 31
    ExplicitTop = 35
    inherited panCaption: TPanel
      Caption = 'LEFT'
    end
  end
  inline kcRight: TfrmKeyCode
    Left = 172
    Top = 35
    Width = 135
    Height = 130
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    TabOrder = 1
    ExplicitLeft = 172
    ExplicitTop = 35
    inherited panCaption: TPanel
      Caption = 'RIGHT'
    end
  end
  inline kcUp: TfrmKeyCode
    Left = 313
    Top = 35
    Width = 135
    Height = 130
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    TabOrder = 2
    ExplicitLeft = 313
    ExplicitTop = 35
    inherited panCaption: TPanel
      Caption = 'UP'
    end
  end
  inline kcDown: TfrmKeyCode
    Left = 454
    Top = 35
    Width = 135
    Height = 130
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    TabOrder = 3
    ExplicitLeft = 454
    ExplicitTop = 35
    inherited panCaption: TPanel
      Caption = 'DOWN'
    end
  end
  inline kcFire1: TfrmKeyCode
    Left = 31
    Top = 210
    Width = 135
    Height = 130
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    TabOrder = 4
    ExplicitLeft = 31
    ExplicitTop = 210
    inherited panCaption: TPanel
      Caption = '1'
    end
  end
  inline kcFire2: TfrmKeyCode
    Left = 172
    Top = 210
    Width = 135
    Height = 130
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    TabOrder = 5
    ExplicitLeft = 172
    ExplicitTop = 210
    inherited panCaption: TPanel
      Caption = '2'
    end
  end
  inline kcFire3: TfrmKeyCode
    Left = 313
    Top = 210
    Width = 135
    Height = 130
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    TabOrder = 6
    ExplicitLeft = 313
    ExplicitTop = 210
    inherited panCaption: TPanel
      Caption = '3'
    end
  end
  inline kcOption1: TfrmKeyCode
    Left = 31
    Top = 387
    Width = 135
    Height = 130
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    TabOrder = 7
    ExplicitLeft = 31
    ExplicitTop = 387
    inherited panCaption: TPanel
      Caption = '1'
    end
  end
  inline kcOption2: TfrmKeyCode
    Left = 172
    Top = 387
    Width = 135
    Height = 130
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    TabOrder = 8
    ExplicitLeft = 172
    ExplicitTop = 387
    inherited panCaption: TPanel
      Caption = '2'
    end
  end
  inline kcOption3: TfrmKeyCode
    Left = 313
    Top = 387
    Width = 135
    Height = 130
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    TabOrder = 9
    ExplicitLeft = 313
    ExplicitTop = 387
    inherited panCaption: TPanel
      Caption = '3'
    end
  end
  inline kcOption4: TfrmKeyCode
    Left = 454
    Top = 387
    Width = 135
    Height = 130
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    TabOrder = 10
    ExplicitLeft = 454
    ExplicitTop = 387
    inherited panCaption: TPanel
      Caption = '4'
    end
  end
end
