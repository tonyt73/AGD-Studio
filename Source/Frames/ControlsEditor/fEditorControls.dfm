object frmEditorControls: TfrmEditorControls
  AlignWithMargins = True
  Left = 0
  Top = 0
  Width = 1355
  Height = 991
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Roboto'
  Font.Style = [fsBold]
  Padding.Left = 16
  Padding.Top = 8
  Padding.Right = 16
  Padding.Bottom = 16
  ParentFont = False
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
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Roboto'
    Font.Style = []
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    ParentFont = False
    TabOrder = 0
    ExplicitLeft = 31
    ExplicitTop = 35
    inherited lblKey: TLabel
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited panCaption: TPanel
      Caption = 'LEFT'
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited edtKey: TEdit
      StyleElements = [seFont, seClient, seBorder]
    end
  end
  inline kcRight: TfrmKeyCode
    Left = 172
    Top = 35
    Width = 135
    Height = 130
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Roboto'
    Font.Style = []
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    ParentFont = False
    TabOrder = 1
    ExplicitLeft = 172
    ExplicitTop = 35
    inherited lblKey: TLabel
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited panCaption: TPanel
      Caption = 'RIGHT'
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited edtKey: TEdit
      StyleElements = [seFont, seClient, seBorder]
    end
  end
  inline kcUp: TfrmKeyCode
    Left = 313
    Top = 35
    Width = 135
    Height = 130
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Roboto'
    Font.Style = []
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    ParentFont = False
    TabOrder = 2
    ExplicitLeft = 313
    ExplicitTop = 35
    inherited lblKey: TLabel
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited panCaption: TPanel
      Caption = 'UP'
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited edtKey: TEdit
      StyleElements = [seFont, seClient, seBorder]
    end
  end
  inline kcDown: TfrmKeyCode
    Left = 454
    Top = 35
    Width = 135
    Height = 130
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    ParentFont = False
    TabOrder = 3
    ExplicitLeft = 454
    ExplicitTop = 35
    inherited lblKey: TLabel
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited panCaption: TPanel
      Caption = 'DOWN'
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited edtKey: TEdit
      StyleElements = [seFont, seClient, seBorder]
    end
  end
  inline kcFire1: TfrmKeyCode
    Left = 31
    Top = 210
    Width = 135
    Height = 130
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    ParentFont = False
    TabOrder = 4
    ExplicitLeft = 31
    ExplicitTop = 210
    inherited lblKey: TLabel
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited panCaption: TPanel
      Caption = '1'
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited edtKey: TEdit
      StyleElements = [seFont, seClient, seBorder]
    end
  end
  inline kcFire2: TfrmKeyCode
    Left = 172
    Top = 210
    Width = 135
    Height = 130
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    ParentFont = False
    TabOrder = 5
    ExplicitLeft = 172
    ExplicitTop = 210
    inherited lblKey: TLabel
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited panCaption: TPanel
      Caption = '2'
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited edtKey: TEdit
      StyleElements = [seFont, seClient, seBorder]
    end
  end
  inline kcFire3: TfrmKeyCode
    Left = 313
    Top = 210
    Width = 135
    Height = 130
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    ParentFont = False
    TabOrder = 6
    ExplicitLeft = 313
    ExplicitTop = 210
    inherited lblKey: TLabel
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited panCaption: TPanel
      Caption = '3'
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited edtKey: TEdit
      StyleElements = [seFont, seClient, seBorder]
    end
  end
  inline kcOption1: TfrmKeyCode
    Left = 31
    Top = 387
    Width = 135
    Height = 130
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Roboto'
    Font.Style = []
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    ParentFont = False
    TabOrder = 7
    ExplicitLeft = 31
    ExplicitTop = 387
    inherited lblKey: TLabel
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited panCaption: TPanel
      Caption = '1'
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited edtKey: TEdit
      StyleElements = [seFont, seClient, seBorder]
    end
  end
  inline kcOption2: TfrmKeyCode
    Left = 172
    Top = 387
    Width = 135
    Height = 130
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Roboto'
    Font.Style = []
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    ParentFont = False
    TabOrder = 8
    ExplicitLeft = 172
    ExplicitTop = 387
    inherited lblKey: TLabel
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited panCaption: TPanel
      Caption = '2'
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited edtKey: TEdit
      StyleElements = [seFont, seClient, seBorder]
    end
  end
  inline kcOption3: TfrmKeyCode
    Left = 313
    Top = 387
    Width = 135
    Height = 130
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Roboto'
    Font.Style = []
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    ParentFont = False
    TabOrder = 9
    ExplicitLeft = 313
    ExplicitTop = 387
    inherited lblKey: TLabel
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited panCaption: TPanel
      Caption = '3'
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited edtKey: TEdit
      StyleElements = [seFont, seClient, seBorder]
    end
  end
  inline kcOption4: TfrmKeyCode
    Left = 454
    Top = 387
    Width = 135
    Height = 130
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Roboto'
    Font.Style = []
    Padding.Left = 7
    Padding.Top = 7
    Padding.Right = 7
    Padding.Bottom = 7
    ParentFont = False
    TabOrder = 10
    ExplicitLeft = 454
    ExplicitTop = 387
    inherited lblKey: TLabel
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited panCaption: TPanel
      Caption = '4'
      StyleElements = [seFont, seClient, seBorder]
    end
    inherited edtKey: TEdit
      StyleElements = [seFont, seClient, seBorder]
    end
  end
end
