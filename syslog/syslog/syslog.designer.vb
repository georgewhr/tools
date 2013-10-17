<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class syslog
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.txtDocument = New System.Windows.Forms.TextBox()
        Me.ofdOpenFile = New System.Windows.Forms.OpenFileDialog()
        Me.sfdSaveFile = New System.Windows.Forms.SaveFileDialog()
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip()
        Me.FileToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.NewToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.OpenToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SaveToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SaveAsToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ExitToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.HelpToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AboutToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.keyword1 = New System.Windows.Forms.TextBox()
        Me.keyword2 = New System.Windows.Forms.TextBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.keyword3 = New System.Windows.Forms.TextBox()
        Me.andLogic = New System.Windows.Forms.CheckBox()
        Me.caseCheck = New System.Windows.Forms.CheckBox()
        Me.MenuStrip1.SuspendLayout()
        Me.SuspendLayout()
        '
        'txtDocument
        '
        Me.txtDocument.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
                    Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.txtDocument.Location = New System.Drawing.Point(1, 171)
        Me.txtDocument.Margin = New System.Windows.Forms.Padding(2, 2, 2, 2)
        Me.txtDocument.Multiline = True
        Me.txtDocument.Name = "txtDocument"
        Me.txtDocument.ScrollBars = System.Windows.Forms.ScrollBars.Both
        Me.txtDocument.Size = New System.Drawing.Size(1019, 371)
        Me.txtDocument.TabIndex = 0
        '
        'ofdOpenFile
        '
        Me.ofdOpenFile.FileName = "ofdOpenFile"
        '
        'sfdSaveFile
        '
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FileToolStripMenuItem, Me.HelpToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Padding = New System.Windows.Forms.Padding(4, 2, 0, 2)
        Me.MenuStrip1.Size = New System.Drawing.Size(1028, 24)
        Me.MenuStrip1.TabIndex = 1
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'FileToolStripMenuItem
        '
        Me.FileToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.NewToolStripMenuItem, Me.OpenToolStripMenuItem, Me.SaveToolStripMenuItem, Me.SaveAsToolStripMenuItem, Me.ExitToolStripMenuItem})
        Me.FileToolStripMenuItem.Name = "FileToolStripMenuItem"
        Me.FileToolStripMenuItem.Size = New System.Drawing.Size(37, 20)
        Me.FileToolStripMenuItem.Text = "File"
        '
        'NewToolStripMenuItem
        '
        Me.NewToolStripMenuItem.Name = "NewToolStripMenuItem"
        Me.NewToolStripMenuItem.Size = New System.Drawing.Size(114, 22)
        Me.NewToolStripMenuItem.Text = "New"
        '
        'OpenToolStripMenuItem
        '
        Me.OpenToolStripMenuItem.Name = "OpenToolStripMenuItem"
        Me.OpenToolStripMenuItem.Size = New System.Drawing.Size(114, 22)
        Me.OpenToolStripMenuItem.Text = "Open"
        '
        'SaveToolStripMenuItem
        '
        Me.SaveToolStripMenuItem.Name = "SaveToolStripMenuItem"
        Me.SaveToolStripMenuItem.Size = New System.Drawing.Size(114, 22)
        Me.SaveToolStripMenuItem.Text = "Save"
        '
        'SaveAsToolStripMenuItem
        '
        Me.SaveAsToolStripMenuItem.Name = "SaveAsToolStripMenuItem"
        Me.SaveAsToolStripMenuItem.Size = New System.Drawing.Size(114, 22)
        Me.SaveAsToolStripMenuItem.Text = "Save As"
        '
        'ExitToolStripMenuItem
        '
        Me.ExitToolStripMenuItem.Name = "ExitToolStripMenuItem"
        Me.ExitToolStripMenuItem.Size = New System.Drawing.Size(114, 22)
        Me.ExitToolStripMenuItem.Text = "Exit"
        '
        'HelpToolStripMenuItem
        '
        Me.HelpToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.AboutToolStripMenuItem})
        Me.HelpToolStripMenuItem.Name = "HelpToolStripMenuItem"
        Me.HelpToolStripMenuItem.Size = New System.Drawing.Size(44, 20)
        Me.HelpToolStripMenuItem.Text = "Help"
        '
        'AboutToolStripMenuItem
        '
        Me.AboutToolStripMenuItem.Name = "AboutToolStripMenuItem"
        Me.AboutToolStripMenuItem.Size = New System.Drawing.Size(107, 22)
        Me.AboutToolStripMenuItem.Text = "About"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(9, 36)
        Me.Label1.Margin = New System.Windows.Forms.Padding(2, 0, 2, 0)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(53, 13)
        Me.Label1.TabIndex = 2
        Me.Label1.Text = "keyword1"
        '
        'keyword1
        '
        Me.keyword1.Location = New System.Drawing.Point(74, 32)
        Me.keyword1.Margin = New System.Windows.Forms.Padding(2, 2, 2, 2)
        Me.keyword1.Name = "keyword1"
        Me.keyword1.Size = New System.Drawing.Size(94, 20)
        Me.keyword1.TabIndex = 3
        '
        'keyword2
        '
        Me.keyword2.Location = New System.Drawing.Point(74, 65)
        Me.keyword2.Margin = New System.Windows.Forms.Padding(2, 2, 2, 2)
        Me.keyword2.Name = "keyword2"
        Me.keyword2.Size = New System.Drawing.Size(94, 20)
        Me.keyword2.TabIndex = 4
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(9, 67)
        Me.Label2.Margin = New System.Windows.Forms.Padding(2, 0, 2, 0)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(53, 13)
        Me.Label2.TabIndex = 5
        Me.Label2.Text = "keyword2"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(9, 105)
        Me.Label3.Margin = New System.Windows.Forms.Padding(2, 0, 2, 0)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(53, 13)
        Me.Label3.TabIndex = 6
        Me.Label3.Text = "keyword3"
        '
        'keyword3
        '
        Me.keyword3.Location = New System.Drawing.Point(74, 101)
        Me.keyword3.Margin = New System.Windows.Forms.Padding(2, 2, 2, 2)
        Me.keyword3.Name = "keyword3"
        Me.keyword3.Size = New System.Drawing.Size(93, 20)
        Me.keyword3.TabIndex = 7
        '
        'andLogic
        '
        Me.andLogic.AutoSize = True
        Me.andLogic.Location = New System.Drawing.Point(221, 35)
        Me.andLogic.Margin = New System.Windows.Forms.Padding(2, 2, 2, 2)
        Me.andLogic.Name = "andLogic"
        Me.andLogic.Size = New System.Drawing.Size(49, 17)
        Me.andLogic.TabIndex = 8
        Me.andLogic.Text = "AND"
        Me.andLogic.UseVisualStyleBackColor = True
        '
        'caseCheck
        '
        Me.caseCheck.AutoSize = True
        Me.caseCheck.Location = New System.Drawing.Point(221, 65)
        Me.caseCheck.Margin = New System.Windows.Forms.Padding(2, 2, 2, 2)
        Me.caseCheck.Name = "caseCheck"
        Me.caseCheck.Size = New System.Drawing.Size(54, 17)
        Me.caseCheck.TabIndex = 9
        Me.caseCheck.Text = "CASE"
        Me.caseCheck.UseVisualStyleBackColor = True
        '
        'syslog
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(1028, 550)
        Me.Controls.Add(Me.caseCheck)
        Me.Controls.Add(Me.andLogic)
        Me.Controls.Add(Me.keyword3)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.keyword2)
        Me.Controls.Add(Me.keyword1)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.txtDocument)
        Me.Controls.Add(Me.MenuStrip1)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Margin = New System.Windows.Forms.Padding(2, 2, 2, 2)
        Me.Name = "syslog"
        Me.Text = "syslog"
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents txtDocument As System.Windows.Forms.TextBox
    Friend WithEvents ofdOpenFile As System.Windows.Forms.OpenFileDialog
    Friend WithEvents sfdSaveFile As System.Windows.Forms.SaveFileDialog
    Friend WithEvents MenuStrip1 As System.Windows.Forms.MenuStrip
    Friend WithEvents FileToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents NewToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents OpenToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents SaveToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents SaveAsToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ExitToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents HelpToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents AboutToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents keyword1 As System.Windows.Forms.TextBox
    Friend WithEvents keyword2 As System.Windows.Forms.TextBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents keyword3 As System.Windows.Forms.TextBox
    Friend WithEvents andLogic As System.Windows.Forms.CheckBox
    Friend WithEvents caseCheck As System.Windows.Forms.CheckBox

End Class
