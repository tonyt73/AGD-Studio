object frmNewTileImage: TfrmNewTileImage
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'New Custom Sized Tile'
  ClientHeight = 225
  ClientWidth = 490
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -15
  Font.Name = 'Roboto'
  Font.Style = []
  Position = poMainFormCenter
  ScreenSnap = True
  OnCreate = FormCreate
  DesignSize = (
    490
    225)
  TextHeight = 18
  object lblWidth: TLabel
    Left = 16
    Top = 144
    Width = 45
    Height = 20
    Anchors = [akLeft, akBottom]
    Caption = 'Width'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Roboto'
    Font.Style = []
    ParentFont = False
    ExplicitTop = 160
  end
  object lblHeight: TLabel
    Left = 147
    Top = 144
    Width = 51
    Height = 20
    Anchors = [akLeft, akBottom]
    Caption = 'Height'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Roboto'
    Font.Style = []
    ParentFont = False
    ExplicitTop = 160
  end
  object LMDHTMLLabel1: TLMDHTMLLabel
    Left = 8
    Top = 8
    Width = 474
    Height = 117
    Alignment = taLeftJustify
    Caption = 
      '<B><FONT SIZE="20px">About custom Tile sizing</FONT></B>'#13#10'<ul>'#13#10 +
      '    <li>Tiles are <B>split</B> into normal-sized tiles during th' +
      'e build process.</li>'#13#10'    <li>The build process handles <B>dupl' +
      'icate</B> tile graphics.</li>'#13#10'    <li>A build <B>error</B> will' +
      ' occur if you run out of tile indexes. (254)</li>'#13#10'    <li>The M' +
      'ap editor <B>can not</B> split a big tile into separate normal t' +
      'iles.</li>'#13#10'</ul>'#13#10
    Layout = tlTop
    Anchors = [akLeft, akTop, akRight, akBottom]
    ExplicitWidth = 326
    ExplicitHeight = 97
  end
  object lblTiles: TLabel
    Left = 290
    Top = 144
    Width = 95
    Height = 20
    Anchors = [akLeft, akBottom]
    Caption = '1 x 1 is 1 tile'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Roboto'
    Font.Style = []
    ParentFont = False
    ExplicitTop = 131
  end
  object Panel1: TPanel
    Left = 0
    Top = 185
    Width = 490
    Height = 40
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    TabStop = True
    ExplicitTop = 102
    ExplicitWidth = 343
    DesignSize = (
      490
      40)
    object btnOk: TButton
      Left = 319
      Top = 10
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'OK'
      Default = True
      ModalResult = 1
      TabOrder = 0
      ExplicitLeft = 172
    end
    object btnCancel: TButton
      Left = 403
      Top = 10
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Cancel = True
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
      ExplicitLeft = 256
    end
  end
  object edtWidth: TElSpinEdit
    Left = 67
    Top = 140
    Width = 64
    Height = 28
    Cursor = crIBeam
    AllowEdit = False
    UseCustomScrollBars = False
    OnChange = edtWidthChange
    Anchors = [akLeft, akBottom]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Roboto'
    Font.Style = [fsBold]
    Flat = True
    ParentFont = False
    TabOrder = 1
    ExplicitTop = 156
  end
  object edtHeight: TElSpinEdit
    Left = 204
    Top = 140
    Width = 64
    Height = 28
    Cursor = crIBeam
    AllowEdit = False
    ButtonFlat = True
    ButtonOldStyled = True
    UseCustomScrollBars = False
    OnChange = edtWidthChange
    Anchors = [akLeft, akBottom]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Roboto'
    Font.Style = [fsBold]
    Flat = True
    ParentFont = False
    TabOrder = 2
    ExplicitTop = 156
  end
end
