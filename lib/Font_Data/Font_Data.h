#pragma once

#include <MD_MAX72xx.h>

/**
 * @brief Two types of fonts for the matrix display.
 * 
 * The first font is a small font that is 3x5 pixels for numbers and 4x5 for the letters.
 * The second font is a pixel font that is 4x7 pixels for numbers and 5x7 for the letters (some of them are 6x7).
 */

MD_MAX72XX::fontType_t small_font[] PROGMEM =
{
	0, 	// 0     
	0, 	// 1     
	0, 	// 2     
	0, 	// 3     
	0, 	// 4     
	0, 	// 5     
	0, 	// 6     
	0, 	// 7     
	0, 	// 8     
	0, 	// 9     
	0, 	// 10     
	0, 	// 11     
	0, 	// 12     
	0, 	// 13     
	0, 	// 14     
	0, 	// 15     
	0, 	// 16     
	0, 	// 17     
	0, 	// 18     
	0, 	// 19     
	0, 	// 20     
	0, 	// 21     
	0, 	// 22     
	0, 	// 23     
	0, 	// 24     
	0, 	// 25     
	0, 	// 26     
	0, 	// 27     
	0, 	// 28     
	0, 	// 29     
	0, 	// 30     
	0, 	// 31     
	1, 0, 	// 32     - 'Space'
	0, 	// 33      - '!'
	0, 	// 34      - '"'
	0, 	// 35      - '#'
	0, 	// 36      - '$'
	0, 	// 37      - '%'
	0, 	// 38      - '&'
	0, 	// 39      - '''
	0, 	// 40      - '('
	0, 	// 41      - ')'
	0, 	// 42      - '*'
	0, 	// 43      - '+'
	0, 	// 44 '
	0, 	// 45      - '-'
	1, 64, 	// 46      - '.'
	0, 	// 47      - '/'
	3, 62, 34, 62, 	// 48    - '0'
	3, 36, 62, 32, 	// 49        - '1'
	3, 58, 42, 46, 	// 50      - '2'
	3, 42, 42, 62, 	// 51      - '3'
	3, 14, 8, 62, 	// 52      - '4'
	3, 46, 42, 58, 	// 53      - '5'
	3, 62, 42, 58, 	// 54    - '6'
	3, 6, 2, 62, 	// 55      - '7'
	3, 62, 42, 62, 	// 56    - '8'
	3, 46, 42, 62, 	// 57    - '9'
	1, 20, 	// 58      - ':'
	0, 	// 59      - ';'
	0, 	// 60      - '<'
	0, 	// 61      - '='
	0, 	// 62      - '>'
	0, 	// 63      - '?'
	0, 	// 64      - '@'
	4, 60, 18, 18, 60, 	// 65     - 'A'
	4, 62, 42, 42, 20, 	// 66     - 'B'
	4, 28, 34, 34, 34, 	// 67     - 'C'
	4, 62, 34, 34, 28, 	// 68     - 'D'
	4, 62, 42, 42, 42, 	// 69     - 'E'
	4, 62, 10, 10, 10, 	// 70       - 'F'
	4, 28, 34, 34, 50, 	// 71      - 'G'
	4, 62, 8, 8, 62, 	// 72      - 'H'
	1, 62, 	// 73      - 'I'
	4, 48, 32, 32, 62, 	// 74      - 'J'
	4, 62, 8, 20, 34, 	// 75      - 'K'
	4, 62, 32, 32, 32, 	// 76      - 'L'
	4, 62, 4, 4, 62, 	// 77      - 'M'
	4, 62, 4, 8, 62, 	// 78      - 'N'
	4, 28, 34, 34, 28, 	// 79      - 'O'
	4, 62, 10, 10, 14, 	// 80      - 'P'
	4, 62, 34, 18, 46, 	// 81      - 'Q'
	4, 62, 10, 26, 36, 	// 82      - 'R'
	4, 36, 42, 42, 18, 	// 83      - 'S'
	3, 2, 62, 2, 	// 84      - 'T'
	4, 62, 32, 32, 62, 	// 85      - 'U'
	4, 30, 48, 48, 30, 	// 86      - 'V'
	4, 62, 16, 16, 62, 	// 87      - 'W'
	4, 54, 8, 8, 54, 	// 88      - 'X'
	3, 6, 56, 6, 	// 89      - 'Y'
	4, 50, 42, 42, 38, 	// 90      - 'Z'
	0, 	// 91      - '['
	0, 	// 92      - '\'
	0, 	// 93      - ']'
	0, 	// 94      - '^'
	0, 	// 95      - '_'
	0, 	// 96      - '`'
	4, 60, 18, 18, 60, 	// 97 - 'a'
	4, 62, 42, 42, 20, 	// 98 - 'b'
	4, 28, 34, 34, 34, 	// 99 - 'c'
	4, 62, 34, 34, 28, 	// 100 - 'd'
	4, 62, 42, 42, 42, 	// 101 - 'e'
	4, 62, 10, 10, 10, 	// 102 - 'f'
	4, 28, 34, 34, 50, 	// 103 - 'g'
	4, 62, 8, 8, 62, 	// 104 - 'h'
	1, 62, 	// 105 - 'i'
	4, 48, 32, 32, 62, 	// 106 - 'j'
	4, 62, 8, 20, 34, 	// 107 - 'k'
	4, 62, 32, 32, 32, 	// 108 - 'l'
	4, 62, 4, 4, 62, 	// 109 - 'm'
	4, 62, 4, 8, 62, 	// 110 - 'n'
	4, 28, 34, 34, 28, 	// 111 - 'o'
	4, 62, 10, 10, 14, 	// 112 - 'p'
	4, 62, 34, 18, 46, 	// 113 - 'q'
	4, 62, 10, 26, 36, 	// 114 - 'r'
	4, 36, 42, 42, 18, 	// 115 - 's'
	3, 2, 62, 2, 	// 116 - 't'
	4, 62, 32, 32, 62, 	// 117 - 'u'
	4, 30, 48, 48, 30, 	// 118 - 'v'
	4, 62, 16, 16, 62, 	// 119 - 'w'
	4, 54, 8, 8, 54, 	// 120 - 'x'
	3, 6, 56, 6, 	// 121 - 'y'
	4, 50, 42, 42, 38, 	// 122 - 'z'
	0, 	// 123
	0, 	// 124
	0, 	// 125
	0, 	// 126
	0, 	// 127
	0, 	// 128
	0, 	// 129
	0, 	// 130
	0, 	// 131
	0, 	// 132
	0, 	// 133
	0, 	// 134
	0, 	// 135
	0, 	// 136
	0, 	// 137
	0, 	// 138
	0, 	// 139
	0, 	// 140
	0, 	// 141
	0, 	// 142
	0, 	// 143
	0, 	// 144
	0, 	// 145
	0, 	// 146
	0, 	// 147
	0, 	// 148
	0, 	// 149
	0, 	// 150
	0, 	// 151
	0, 	// 152
	0, 	// 153
	0, 	// 154
	0, 	// 155
	0, 	// 156
	0, 	// 157
	0, 	// 158
	0, 	// 159
	0, 	// 160
	0, 	// 161
	0, 	// 162
	0, 	// 163
	0, 	// 164
	0, 	// 165
	0, 	// 166
	0, 	// 167
	0, 	// 168
	0, 	// 169
	0, 	// 170
	0, 	// 171
	0, 	// 172
	0, 	// 173
	0, 	// 174
	0, 	// 175
	0, 	// 176
	0, 	// 177
	0, 	// 178
	0, 	// 179
	0, 	// 180
	0, 	// 181
	0, 	// 182
	0, 	// 183
	0, 	// 184
	0, 	// 185
	0, 	// 186
	0, 	// 187
	0, 	// 188
	0, 	// 189
	0, 	// 190
	0, 	// 191
	0, 	// 192
	0, 	// 193
	0, 	// 194
	0, 	// 195
	0, 	// 196
	0, 	// 197
	0, 	// 198
	0, 	// 199
	0, 	// 200
	0, 	// 201
	0, 	// 202
	0, 	// 203
	0, 	// 204
	0, 	// 205
	0, 	// 206
	0, 	// 207
	0, 	// 208
	0, 	// 209
	0, 	// 210
	0, 	// 211
	0, 	// 212
	0, 	// 213
	0, 	// 214
	0, 	// 215
	0, 	// 216
	0, 	// 217
	0, 	// 218
	0, 	// 219
	0, 	// 220
	0, 	// 221
	0, 	// 222
	0, 	// 223
	0, 	// 224
	0, 	// 225
	0, 	// 226
	0, 	// 227
	0, 	// 228
	0, 	// 229
	0, 	// 230
	0, 	// 231
	0, 	// 232
	0, 	// 233
	0, 	// 234
	0, 	// 235
	0, 	// 236
	0, 	// 237
	0, 	// 238
	0, 	// 239
	0, 	// 240
	0, 	// 241
	0, 	// 242
	0, 	// 243
	0, 	// 244
	0, 	// 245
	0, 	// 246
	0, 	// 247
	0, 	// 248
	0, 	// 249
	0, 	// 250
	0, 	// 251
	0, 	// 252
	0, 	// 253
	0, 	// 254
	0, 	// 255
};

MD_MAX72XX::fontType_t pixel_font[] PROGMEM =
{
	0, 	// 0      
	0, 	// 1      
	0, 	// 2      
	0, 	// 3      
	0, 	// 4      
	0, 	// 5      
	0, 	// 6      
	0, 	// 7      
	0, 	// 8      
	0, 	// 9      
	0, 	// 10      
	0, 	// 11      
	0, 	// 12      
	0, 	// 13      
	0, 	// 14      
	0, 	// 15      
	0, 	// 16      
	0, 	// 17      
	0, 	// 18      
	0, 	// 19      
	0, 	// 20      
	0, 	// 21      
	0, 	// 22      
	0, 	// 23      
	0, 	// 24      
	0, 	// 25      
	0, 	// 26      
	0, 	// 27      
	0, 	// 28      
	0, 	// 29      
	0, 	// 30      
	0, 	// 31      
	1, 0, 	// 32      - 'Space'
	1, 95, 	// 33       - '!'
	4, 4, 3, 4, 3, 	// 34       - '"'
	5, 20, 127, 20, 127, 20, 	// 35       - '#'
	5, 4, 42, 107, 42, 16, 	// 36       - '$'
	5, 70, 54, 8, 54, 49, 	// 37       - '%'
	5, 48, 74, 93, 50, 72, 	// 38       - '&'
	2, 4, 3, 	// 39       - '''
	3, 28, 34, 65, 	// 40       - '('
	3, 65, 34, 28, 	// 41       - ')'
	4, 5, 2, 2, 5, 	// 42       - '*'
	5, 16, 16, 124, 16, 16, 	// 43       - '+'
	1, 96, 	// 44  '
	5, 16, 16, 16, 16, 16, 	// 45       - '-'
	1, 64, 	// 46       - '.'
	5, 64, 48, 8, 6, 1, 	// 47       - '/'
	4, 127, 81, 73, 127, 	// 48     - '0'
	4, 0, 66, 127, 64, 	// 49        - '1'
	4, 121, 73, 73, 79, 	// 50      - '2'
	4, 99, 73, 73, 119, 	// 51      - '3'
	4, 15, 8, 8, 127, 	// 52        - '4'
	4, 79, 73, 73, 121, 	// 53      - '5'
	4, 127, 73, 73, 121, 	// 54     - '6'
	4, 3, 1, 125, 3, 	// 55        - '7'
	4, 119, 73, 73, 119, 	// 56     - '8'
	4, 79, 73, 73, 127, 	// 57      - '9'
	1, 20, 	// 58       - ':'
	1, 88, 	// 59       - ';'
	3, 16, 40, 68, 	// 60       - '<'
	5, 40, 40, 40, 40, 40, 	// 61       - '='
	3, 68, 40, 16, 	// 62       - '>'
	5, 6, 1, 81, 9, 6, 	// 63       - '?'
	6, 62, 65, 93, 93, 81, 30, 	// 64       - '@'
	5, 126, 127, 17, 17, 126, 	// 65      - 'A'
	5, 127, 127, 73, 73, 54, 	// 66      - 'B'
	5, 62, 127, 65, 65, 34, 	// 67      - 'C'
	5, 127, 127, 65, 65, 62, 	// 68      - 'D'
	5, 127, 127, 73, 73, 73, 	// 69      - 'E'
	5, 127, 127, 9, 9, 9, 	// 70        - 'F'
	5, 62, 127, 65, 73, 58, 	// 71       - 'G'
	5, 127, 127, 8, 8, 127, 	// 72       - 'H'
	2, 127, 127, 	// 73       - 'I'
	5, 32, 64, 64, 127, 63, 	// 74       - 'J'
	5, 127, 127, 8, 20, 99, 	// 75       - 'K'
	5, 127, 127, 64, 64, 64, 	// 76       - 'L'
	6, 127, 127, 2, 4, 2, 127, 	// 77       - 'M'
	6, 127, 127, 4, 8, 16, 127, 	// 78       - 'N'
	5, 62, 127, 65, 65, 62, 	// 79       - 'O'
	5, 127, 127, 17, 17, 14, 	// 80       - 'P'
	5, 62, 127, 65, 33, 94, 	// 81       - 'Q'
	5, 127, 127, 25, 41, 70, 	// 82       - 'R'
	5, 38, 79, 73, 121, 50, 	// 83       - 'S'
	6, 1, 1, 127, 127, 1, 1, 	// 84       - 'T'
	5, 63, 127, 64, 64, 63, 	// 85       - 'U'
	5, 31, 63, 96, 32, 31, 	// 86       - 'V'
	6, 63, 63, 96, 48, 96, 63, 	// 87       - 'W'
	6, 113, 123, 14, 4, 10, 113, 	// 88       - 'X'
	8, 1, 3, 126, 124, 2, 1, 0, 0, 	// 89       - 'Y'
	8, 97, 113, 93, 71, 67, 0, 0, 0, 	// 90       - 'Z'
	3, 127, 65, 65, 	// 91       - '['
	5, 1, 6, 8, 48, 64, 	// 92        - '\'
	3, 65, 65, 127, 	// 93       - ']'
	3, 6, 1, 6, 	// 94       - '^'
	3, 64, 64, 64, 	// 95       - '_'
	2, 1, 6, 	// 96       - '`'
	5, 126, 127, 17, 17, 126, 	// 97      - 'a'
	5, 127, 127, 73, 73, 54, 	// 98      - 'b'
	5, 62, 127, 65, 65, 34, 	// 99      - 'c'
	5, 127, 127, 65, 65, 62, 	// 100      - 'd'
	5, 127, 127, 73, 73, 73, 	// 101      - 'e'
	5, 127, 127, 9, 9, 9, 	// 102        - 'f'
	5, 62, 127, 65, 73, 58, 	// 103       - 'g'
	5, 127, 127, 8, 8, 127, 	// 104       - 'h'
	2, 127, 127, 	// 105       - 'i'
	5, 32, 64, 64, 127, 63, 	// 106       - 'j'
	5, 127, 127, 8, 20, 99, 	// 107       - 'k'
	5, 127, 127, 64, 64, 64, 	// 108       - 'l'
	6, 127, 127, 2, 4, 2, 127, 	// 109       - 'm'
	6, 127, 127, 4, 8, 16, 127, 	// 110       - 'n'
	5, 62, 127, 65, 65, 62, 	// 111       - 'o'
	5, 127, 127, 17, 17, 14, 	// 112       - 'p'
	5, 62, 127, 65, 33, 94, 	// 113       - 'q'
	5, 127, 127, 25, 41, 70, 	// 114       - 'r'
	5, 38, 79, 73, 121, 50, 	// 115       - 's'
	6, 1, 1, 127, 127, 1, 1, 	// 116       - 't'
	5, 63, 127, 64, 64, 63, 	// 117       - 'u'
	5, 31, 63, 96, 32, 31, 	// 118       - 'v'
	6, 63, 63, 96, 48, 96, 63, 	// 119       - 'w'
	6, 113, 123, 14, 4, 10, 113, 	// 120       - 'x'
	8, 1, 3, 126, 124, 2, 1, 0, 0, 	// 121       - 'y'
	8, 97, 113, 93, 71, 67, 0, 0, 0, 	// 122       - 'z'
	3, 8, 119, 65, 	// 123       - '{'
	1, 127, 	// 124      - '|'
	3, 65, 119, 8, 	// 125      
	6, 16, 8, 8, 16, 16, 8, 	// 126      
	0, 	// 127      
	6, 20, 62, 85, 85, 65, 34, 	// 128      
	0, 	// 129      
	1, 96, 	// 130      
	0, 	// 131      
	0, 	// 132      
	5, 64, 0, 64, 0, 64, 	// 133      
	5, 4, 4, 127, 4, 4, 	// 134      
	0, 	// 135      
	0, 	// 136      
	0, 	// 137      
	0, 	// 138      
	0, 	// 139      
	0, 	// 140      
	0, 	// 141      
	0, 	// 142      
	0, 	// 143      
	0, 	// 144      
	0, 	// 145      
	0, 	// 146      
	0, 	// 147      
	0, 	// 148      
	1, 2, 	// 149      
	3, 16, 16, 16, 	// 150      
	3, 64, 64, 64, 	// 151      
	0, 	// 152      
	7, 1, 7, 1, 0, 7, 2, 7, 	// 153      
	0, 	// 154      
	0, 	// 155      
	0, 	// 156      
	0, 	// 157      
	0, 	// 158      
	0, 	// 159      
	0, 	// 160      
	0, 	// 161      
	0, 	// 162      
	0, 	// 163      
	0, 	// 164      
	0, 	// 165      
	1, 54, 	// 166      
	0, 	// 167      
	0, 	// 168      
	0, 	// 169      
	0, 	// 170      
	5, 16, 40, 84, 40, 68, 	// 171      
	4, 8, 8, 8, 24, 	// 172      
	0, 	// 173      
	0, 	// 174      
	0, 	// 175      
	3, 7, 5, 7, 	// 176      
	5, 72, 72, 92, 72, 72, 	// 177      
	2, 13, 11, 	// 178      
	2, 21, 31, 	// 179      
	0, 	// 180      
	0, 	// 181      
	0, 	// 182      
	0, 	// 183      
	0, 	// 184      
	0, 	// 185      
	0, 	// 186      
	5, 68, 40, 84, 40, 16, 	// 187      
	0, 	// 188      
	0, 	// 189      
	0, 	// 190      
	5, 48, 72, 69, 64, 48, 	// 191      
	0, 	// 192      
	0, 	// 193      
	0, 	// 194      
	0, 	// 195      
	0, 	// 196      
	0, 	// 197      
	7, 124, 18, 17, 127, 73, 73, 65, 	// 198      
	0, 	// 199      
	0, 	// 200      
	0, 	// 201      
	0, 	// 202      
	0, 	// 203      
	0, 	// 204      
	0, 	// 205      
	0, 	// 206      
	0, 	// 207      
	0, 	// 208      
	0, 	// 209      
	0, 	// 210      
	0, 	// 211      
	0, 	// 212      
	0, 	// 213      
	0, 	// 214      
	5, 68, 40, 16, 40, 68, 	// 215      
	0, 	// 216      
	0, 	// 217      
	0, 	// 218      
	0, 	// 219      
	0, 	// 220      
	0, 	// 221      
	0, 	// 222      
	0, 	// 223      
	0, 	// 224      
	0, 	// 225      
	0, 	// 226      
	0, 	// 227      
	0, 	// 228      
	0, 	// 229      
	0, 	// 230      
	0, 	// 231      
	0, 	// 232      
	0, 	// 233      
	0, 	// 234      
	0, 	// 235      
	0, 	// 236      
	0, 	// 237      
	0, 	// 238      
	0, 	// 239      
	0, 	// 240      
	0, 	// 241      
	0, 	// 242      
	0, 	// 243      
	0, 	// 244      
	0, 	// 245      
	0, 	// 246      
	5, 16, 16, 84, 16, 16, 	// 247      
	0, 	// 248      
	0, 	// 249      
	0, 	// 250      
	0, 	// 251      
	0, 	// 252      
	0, 	// 253      
	0, 	// 254      
	0, 	// 255
};