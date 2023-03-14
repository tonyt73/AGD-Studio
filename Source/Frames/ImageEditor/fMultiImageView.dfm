object MultiImageViewFrame: TMultiImageViewFrame
  Left = 0
  Top = 0
  Width = 435
  Height = 61
  HorzScrollBar.ParentColor = False
  HorzScrollBar.Smooth = True
  HorzScrollBar.Style = ssHotTrack
  HorzScrollBar.Tracking = True
  VertScrollBar.Tracking = True
  VertScrollBar.Visible = False
  Align = alTop
  AutoScroll = True
  DoubleBuffered = True
  Ctl3D = False
  ParentCtl3D = False
  ParentDoubleBuffered = False
  TabOrder = 0
  OnMouseWheel = FrameMouseWheel
  object panImages: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 41
    BevelOuter = bvNone
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 0
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 196
    Top = 12
  end
end
