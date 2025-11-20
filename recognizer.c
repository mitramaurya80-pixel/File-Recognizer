#include <stdio.h>
#include <stdlib.h>


// Return file extension (including leading dot) on match, NULL on error/unknown
const char *file_recognizer(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    unsigned char buffer[8];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    if (bytesRead < 8) {
        return NULL;
    }

    // Images
    // PNG
    if (buffer[0] == 0x89 && buffer[1] == 0x50 && buffer[2] == 0x4E &&
        buffer[3] == 0x47 && buffer[4] == 0x0D && buffer[5] == 0x0A &&
        buffer[6] == 0x1A && buffer[7] == 0x0A) {
        return ".png";
    }

    // JPEG
    if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF) {
        return ".jpg";
    }

    // GIF
    if ((buffer[0] == 'G' && buffer[1] == 'I' && buffer[2] == 'F' &&
         buffer[3] == '8' && (buffer[4] == '7' || buffer[4] == '9') &&
         buffer[5] == 'a')) {
        return ".gif";
    }

    // BMP
    if (buffer[0] == 0x42 && buffer[1] == 0x4D) {
        return ".bmp";
    }

    // TIFF (little-endian)
    if (buffer[0] == 0x49 && buffer[1] == 0x49 &&
        buffer[2] == 0x2A && buffer[3] == 0x00) {
        return ".tiff";
    }

    // ICO
    if (buffer[0] == 0x00 && buffer[1] == 0x00 &&
        buffer[2] == 0x01 && buffer[3] == 0x00) {
        return ".ico";
    }

    // PSD
    if (buffer[0] == 0x38 && buffer[1] == 0x42 &&
        buffer[2] == 0x50 && buffer[3] == 0x53) {
        return ".psd";
    }

    // Audio
    // WAV / RIFF-based (heuristic)
    if (buffer[0] == 0x52 && buffer[1] == 0x49 &&
        buffer[2] == 0x46 && buffer[3] == 0x46) {
        // ambiguous RIFF container; return generic .wav as a common RIFF audio container
        return ".wav";
    }

    // OGG
    if (buffer[0] == 0x4F && buffer[1] == 0x67 &&
        buffer[2] == 0x67 && buffer[3] == 0x53) {
        return ".ogg";
    }

    // FLAC
    if (buffer[0] == 0x66 && buffer[1] == 0x4C &&
        buffer[2] == 0x61 && buffer[3] == 0x43) {
        return ".flac";
    }

    // MP3 (ID3)
    if (buffer[0] == 0x49 && buffer[1] == 0x44 &&
        buffer[2] == 0x33) {
        return ".mp3";
    }

    // Video
    // MPEG (system stream)
    if (buffer[0] == 0x00 && buffer[1] == 0x00 &&
        buffer[2] == 0x01 && buffer[3] == 0xBA) {
        return ".mpeg";
    }

    // MKV
    if (buffer[0] == 0x1A && buffer[1] == 0x45 &&
        buffer[2] == 0xDF && buffer[3] == 0xA3) {
        return ".mkv";
    }

    // MP4 / ISO Base Media file format (ftyp)
    if (buffer[0] == 0x00 && buffer[1] == 0x00 &&
        buffer[2] == 0x00 && (buffer[3] == 0x18 || buffer[3] == 0x20) &&
        buffer[4] == 0x66 && buffer[5] == 0x74 &&
        buffer[6] == 0x79 && buffer[7] == 0x70) {
        return ".mp4";
    }

    // Archives
    // ZIP
    if (buffer[0] == 0x50 && buffer[1] == 0x4B &&
       (buffer[2] == 0x03 || buffer[2] == 0x05 || buffer[2] == 0x07) &&
       (buffer[3] == 0x04 || buffer[3] == 0x06 || buffer[3] == 0x08)) {
        return ".zip";
    }

    // RAR
    if (buffer[0] == 0x52 && buffer[1] == 0x61 &&
        buffer[2] == 0x72 && buffer[3] == 0x21) {
        return ".rar";
    }

    // 7z
    if (buffer[0] == 0x37 && buffer[1] == 0x7A &&
        buffer[2] == 0xBC && buffer[3] == 0xAF &&
        buffer[4] == 0x27 && buffer[5] == 0x1C) {
        return ".7z";
    }

    // Compression
    if (buffer[0] == 0x1F && buffer[1] == 0x8B) {
        return ".gz";
    }
    if (buffer[0] == 0x42 && buffer[1] == 0x5A &&
        buffer[2] == 0x68) {
        return ".bz2";
    }

    // Executables
    // ELF
    if (buffer[0] == 0x7F && buffer[1] == 'E' && buffer[2] == 'L' &&
        buffer[3] == 'F') {
        return ".elf";
    }

    // PE (Windows) - 'MZ'
    if (buffer[0] == 'M' && buffer[1] == 'Z') {
        return ".exe";
    }

    // Mach-O (common magic)
    if (buffer[0] == 0xFE && buffer[1] == 0xED &&
        buffer[2] == 0xFA && buffer[3] == 0xCE) {
        return ".macho";
    }

    // Documents
    // PDF
    if (buffer[0] == 0x25 && buffer[1] == 0x50 && buffer[2] == 0x44 &&
        buffer[3] == 0x46) {
        return ".pdf";
    }

    // PostScript
    if (buffer[0] == 0x25 && buffer[1] == 0x21 &&
        buffer[2] == 0x50 && buffer[3] == 0x53) {
        return ".ps";
    }

    // RTF
    if (buffer[0] == 0x7B && buffer[1] == 0x5C &&
        buffer[2] == 0x72 && buffer[3] == 0x74 &&
        buffer[4] == 0x66) {
        return ".rtf";
    }

    // Microsoft Office (compound file / old formats)
    if (buffer[0] == 0xD0 && buffer[1] == 0xCF &&
        buffer[2] == 0x11 && buffer[3] == 0xE0) {
        return ".doc"; // old compound file formats (could be doc/xls/ppt)
    }

    // Fonts
    // TrueType
    if (buffer[0] == 0x00 && buffer[1] == 0x01 &&
        buffer[2] == 0x00 && buffer[3] == 0x00) {
        return ".ttf";
    }

    // OpenType (OTTO)
    if (buffer[0] == 0x4F && buffer[1] == 0x54 &&
        buffer[2] == 0x54 && buffer[3] == 0x4F) {
        return ".otf";
    }

    // WOFF
    if (buffer[0] == 0x77 && buffer[1] == 0x4F &&
        buffer[2] == 0x46 && buffer[3] == 0x46) {
        return ".woff";
    }

    // Database
    // SQLite
    if (buffer[0] == 0x53 && buffer[1] == 0x51 &&
        buffer[2] == 0x4C && buffer[3] == 0x69 &&
        buffer[4] == 0x74 && buffer[5] == 0x65) {
        return ".sqlite";
    }

    // LaTeX (heuristic)
    if (buffer[0] == 0x7B && buffer[1] == 0x5C &&
        buffer[2] == 0x70 && buffer[3] == 0x61 &&
        buffer[4] == 0x67 && buffer[5] == 0x65) {
        return ".tex";
    }

    // Misc / duplicates left as heuristics
    if (buffer[0] == 0x50 && buffer[1] == 0x4D) {
        return ".bin";
    }

    return NULL;
}
