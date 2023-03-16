object frmKeyCode: TfrmKeyCode
  Left = 0
  Top = 0
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
  OnMouseDown = FrameMouseDown
  OnMouseEnter = edtKeyMouseEnter
  OnMouseLeave = edtKeyMouseLeave
  DesignSize = (
    135
    130)
  object lblKey: TLabel
    Left = 7
    Top = 95
    Width = 121
    Height = 28
    Align = alBottom
    Alignment = taCenter
    Anchors = [akLeft, akTop, akRight, akBottom]
    AutoSize = False
    Caption = 'Space - ASCII: 32'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Roboto'
    Font.Style = []
    ParentFont = False
    Layout = tlCenter
    OnMouseDown = FrameMouseDown
    OnMouseEnter = edtKeyMouseEnter
    OnMouseLeave = edtKeyMouseLeave
    ExplicitTop = 93
    ExplicitHeight = 34
  end
  object panCaption: TPanel
    Left = 7
    Top = 7
    Width = 121
    Height = 29
    Align = alTop
    BevelOuter = bvNone
    Caption = 'panCaption'
    Color = clActiveCaption
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clCaptionText
    Font.Height = -16
    Font.Name = 'Roboto'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    TabOrder = 0
    OnMouseDown = FrameMouseDown
    OnMouseEnter = edtKeyMouseEnter
    OnMouseLeave = edtKeyMouseLeave
  end
  object edtKey: TEdit
    Left = 7
    Top = 39
    Width = 121
    Height = 46
    Alignment = taCenter
    Anchors = [akLeft, akTop, akRight]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'Roboto'
    Font.Style = [fsBold]
    MaxLength = 3
    ParentFont = False
    TabOrder = 1
    OnChange = edtKeyChange
    OnEnter = edtKeyMouseEnter
    OnExit = edtKeyMouseLeave
    OnKeyPress = edtKeyKeyPress
    OnMouseEnter = edtKeyMouseEnter
    OnMouseLeave = edtKeyMouseLeave
  end
end
