Public Class syslog
    Dim documentName As String = ""
    Dim isChanged As Boolean = False
    Dim inputFile As System.IO.StreamReader
    Dim outputFIle As System.IO.StreamWriter
    Dim keywordReadtFile As System.IO.StreamReader
    Dim keywordWritetFile As System.IO.StreamWriter
    Dim stringReader As String
    Dim FILE_NAME As String = "C:\Users\TE116359\Documents\vb\keywords.txt"
    Dim keyword(3) As String


    Private Sub syslog_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

    End Sub

    Sub Process()
        Dim regDate As Date = Date.Now()
        Dim strDate As String = regDate.ToString("ddMMMyyyy")
        Dim i As Integer

        If My.Computer.FileSystem.FileExists(FILE_NAME) Then
            'keywordReadtFile = System.IO.File.OpenText(FILE_NAME)
            Dim objWriter As New System.IO.StreamWriter(FILE_NAME, True)

            For i = 0 To 2

                If keyword(i) <> "" Then

                    objWriter.WriteLine(keyword(i))
                End If

            Next
            objWriter.Close()


        Else
            Dim file As System.IO.FileStream
            file = System.IO.File.Create(FILE_NAME)
            file.Close()
            Dim objWriter As System.IO.StreamWriter
            'objWriter = System.IO.File.CreateText(FILE_NAME)
            'keywordReadtFile = System.IO.File.OpenText(FILE_NAME)

            objWriter = System.IO.File.AppendText(FILE_NAME)
            For i = 0 To 2

                If keyword(i) <> "" Then

                    objWriter.WriteLine(keyword(i))
                End If

            Next
            objWriter.Close()
        End If





        outputFIle = System.IO.File.CreateText("C:\Users\TE116359\Documents\vb\test.txt")

        If ofdOpenFile.ShowDialog = DialogResult.OK Then
            documentName = ofdOpenFile.FileName
            inputFile = System.IO.File.OpenText(documentName)

            Do While inputFile.Peek() >= 0
                stringReader = inputFile.ReadLine
                If andLogic.CheckState = 1 Then
                    andLgc()

                Else
                    orLgc()

                End If


            Loop

            outputFIle.Close()
            inputFile.Close()

        End If
    End Sub

    Sub andLgc()

        If caseCheck.CheckState = 1 Then

            If stringReader.Contains(keyword1.Text) And stringReader.Contains(keyword2.Text) And stringReader.Contains(keyword3.Text) Then
                outputFIle.WriteLine(stringReader)
            End If
        Else
            Dim lowerCase As String = stringReader.ToLower
            If lowerCase.Contains(keyword1.Text) And lowerCase.Contains(keyword2.Text) And lowerCase.Contains(keyword3.Text) Then

                outputFIle.WriteLine(stringReader)
            End If
        End If


    End Sub

    Sub orLgc()
        If caseCheck.CheckState = 1 Then

            For i = 0 To 2
                If keyword(i) <> "" Then
                    If stringReader.Contains(keyword(i)) Then
                        outputFIle.WriteLine(stringReader)
                    End If

                End If
            Next

        Else
            Dim lowerCase As String = stringReader.ToLower

            For i = 0 To 2
                If keyword(i) <> "" Then
                    If lowerCase.Contains(keyword(i)) Then
                        outputFIle.WriteLine(stringReader)
                    End If

                End If
            Next
        End If



    End Sub

    Private Sub SaveFileDialog1_FileOk(ByVal sender As System.Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles sfdSaveFile.FileOk

    End Sub

    Private Sub txtDocument_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtDocument.TextChanged

    End Sub

    Private Sub FileToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles FileToolStripMenuItem.Click

    End Sub

    Private Sub OpenToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenToolStripMenuItem.Click
        If isChanged = True Then
            If MessageBox.Show("The current document is not saved") Then
                Process()

            End If

        Else
            Process()
        End If
    End Sub

    Private Sub keywod1_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles keyword1.TextChanged
        keyword(0) = keyword1.Text
    End Sub

    Private Sub Label2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Label2.Click

    End Sub

    Private Sub keyword2_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles keyword2.TextChanged
        keyword(1) = keyword2.Text
    End Sub

    Private Sub keyword3_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles keyword3.TextChanged
        keyword(2) = keyword3.Text()
    End Sub

    Private Sub caseCheck_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles caseCheck.CheckedChanged

    End Sub
End Class
