import java.io.BufferedReader
import java.io.File
import java.io.InputStream
import java.nio.file.Paths

const val RELEASE = false

fun main(args: Array<String>) {
    val path = if (RELEASE)  "" else Paths.get("").toAbsolutePath()
    val reader: BufferedReader = File("$path/problem1.in").inputStream().bufferedReader()
    val word = reader.readLine()
    val (n, m, k) = reader.readLine()!!.split(' ').map(String::toInt)
    data class State(val t: ArrayList<Pair<Int, Char>>, var isAllowing: Boolean)
    val tree = Array(n, { State(ArrayList(), false) })
    val allowingStates = reader.readLine()!!.split(' ').map(String::toInt)
    allowingStates.forEach { ind -> tree[ind - 1].isAllowing = true }
    for (line in reader.readLines()) {
        val sl = line.split(' ')
        tree[sl[0].toInt() - 1].t.add(Pair(sl[1].toInt() - 1, sl[2].single()))
    }
    var current = 0
    for (c in word) {
        var flag = false
        for (state in tree[current].t) {
            if (state.second == c) {
                current = state.first
                flag = true
                break
            }
        }
        if (!flag)
            break
    }
    if (tree[current].isAllowing)
        println("Accepts")
    else
        println("Rejects")
}