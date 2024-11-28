inherited frmEditorWindow: TfrmEditorWindow
  Font.Name = 'Roboto'
  ParentFont = False
  OnResize = FrameResize
  object imgView: TImage
    Left = 71
    Top = 71
    Width = 757
    Height = 590
    OnMouseMove = imgViewMouseMove
  end
  object sbrWindow: TStatusBar
    Left = 0
    Top = 421
    Width = 624
    Height = 20
    Panels = <
      item
        Text = 'Left: 0'
        Width = 100
      end
      item
        Text = 'Top: 0'
        Width = 100
      end
      item
        Text = 'Right: 0'
        Width = 100
      end
      item
        Text = 'Bottom: 0'
        Width = 100
      end
      item
        Text = 'Width: 0'
        Width = 100
      end
      item
        Text = 'Height: 0'
        Width = 100
      end
      item
        Width = 50
      end>
  end
  object actList: TActionList
    Left = 72
    Top = 16
    object actMoveLeft: TAction
      Caption = 'actMoveLeft'
      ShortCut = 37
      OnExecute = actMoveLeftExecute
    end
    object actMoveRight: TAction
      Caption = 'actMoveRight'
      ShortCut = 39
      OnExecute = actMoveRightExecute
    end
    object actMoveUp: TAction
      Caption = 'actMoveUp'
      ShortCut = 38
      OnExecute = actMoveUpExecute
    end
    object actMoveDown: TAction
      Caption = 'actMoveDown'
      ShortCut = 40
      OnExecute = actMoveDownExecute
    end
    object actWidthDec: TAction
      Caption = 'actWidthDec'
      ShortCut = 8229
      OnExecute = actWidthDecExecute
    end
    object actWidthInc: TAction
      Caption = 'actWidthInc'
      ShortCut = 8231
      OnExecute = actWidthIncExecute
    end
    object actHeightDec: TAction
      Caption = 'actHeightDec'
      ShortCut = 8230
      OnExecute = actHeightDecExecute
    end
    object actHeightInc: TAction
      Caption = 'actHeightInc'
      ShortCut = 8232
      OnExecute = actHeightIncExecute
    end
  end
end
