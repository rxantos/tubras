//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006-2007 Tubras Software, Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#ifndef _TFILE_H_
#define _TFILE_H_

namespace Tubras
{

    typedef std::vector<TString> vector_string;
    typedef std::ios::openmode ios_openmode;
    typedef int ios_openmode;


    class TSearchPath 
    {
    public:
        class TResults 
        {
        public:
            TResults();
            TResults(const TResults &copy);
            void operator = (const TResults &copy);
            ~TResults();

            void clear();
            int get_num_files() const;
            const class TFile &get_file(int n) const;

        public:
            void add_file(const class TFile &file);

        private:
            typedef std::vector<class TFile> Files;
            Files _files;
        };

    public:
        TSearchPath();
        TSearchPath(const TString &path, const TString &delimiters = ": \n\t");
        TSearchPath(const TSearchPath &copy);
        void operator = (const TSearchPath &copy);
        ~TSearchPath();

        void clear();
        void append_directory(const class TFile &directory);
        void prepend_directory(const class TFile &directory);
        void append_path(const TString &path,
            const TString &delimiters = ": \n\t");
        void append_path(const TSearchPath &path);
        void prepend_path(const TSearchPath &path);

        bool is_empty() const;
        int get_num_directories() const;
        const class TFile &get_directory(int n) const;

        class TFile find_file(const class TFile &filename) const;
        int find_all_files(const class TFile &filename, TResults &results) const;

        inline static class TFile
            search_path(const class TFile &filename, const TString &path,
            const TString &delimiters = ": \n\t");

        void output(std::ostream &out, const TString &separator = ":") const;
        void write(std::ostream &out, int indent_level = 0) const;

    private:
        typedef std::vector<class TFile> Directories;
        Directories _directories;
    };

    inline std::ostream &operator << (std::ostream &out, const TSearchPath &sp) {
        sp.output(out);
        return out;
    }


    class TExecutionEnvironment {
    public:
        static TString get_environment_variable(const TString &var);
        static TString expand_string(const TString &str);
        static class TFile get_cwd();
    };

    class TFile
    {
    public:

        static Ogre::Archive *findArchive(TString resourceGroup,TString& TFile);

        enum Type {
            // These type values must fit within the bits allocated for
            // F_type, below.
            T_general    = 0x00,
            T_dso        = 0x01,
            T_executable = 0x02,
            // Perhaps other types will be added later.
        };

    public:
        enum Flags {
            F_type            = 0x0f,
            F_binary          = 0x10,
            F_text            = 0x20,
        };

    public:
        inline TFile(const TString &filename = "");
        inline TFile(const char *filename);
        inline TFile(const TFile &copy);
        TFile(const TFile &dirname, const TFile &basename);
        inline ~TFile();

        // Static constructors to explicitly create a TFile that refers
        // to a text or binary file.  This is in lieu of calling set_text()
        // or set_binary() or set_type().
        inline static TFile text_filename(const TString &filename);
        inline static TFile binary_filename(const TString &filename);
        inline static TFile dso_filename(const TString &filename);
        inline static TFile executable_filename(const TString &filename);

        static TFile from_os_specific(const TString &os_specific,
            Type type = T_general);
        static TFile expand_from(const TString &user_string, 
            Type type = T_general);
        static TFile temporary(const TString &dirname, const TString &prefix,
            Type type = T_general);

        // Assignment is via the = operator.
        inline TFile &operator = (const TString &filename);
        inline TFile &operator = (const char *filename);
        inline TFile &operator = (const TFile &copy);

        // And retrieval is by any of the classic TString operations.
        inline operator const TString & () const;
        inline const char *c_str() const;
        inline bool empty() const;
        inline size_t length() const;
        inline char operator [] (int n) const;

        // Or, you can use any of these.
        inline TString get_fullpath() const;
        inline TString get_dirname() const;
        inline TString get_basename() const;
        inline TString get_fullpath_wo_extension() const;
        inline TString get_basename_wo_extension() const;
        inline TString get_extension() const;

        // You can also use any of these to reassign pieces of the TFile.
        void set_fullpath(const TString &s);
        void set_dirname(const TString &s);
        void set_basename(const TString &s);
        void set_fullpath_wo_extension(const TString &s);
        void set_basename_wo_extension(const TString &s);
        void set_extension(const TString &s);

        // Setting these flags appropriately is helpful when opening or
        // searching for a file; it helps the TFile resolve OS-specific
        // conventions (for instance, that dynamic library names should
        // perhaps be changed from .so to .dll).
        inline void set_binary();
        inline void set_text();
        inline bool is_binary() const;
        inline bool is_text() const;

        inline void set_type(Type type);
        inline Type get_type() const;

        void extract_components(vector_string &components) const;
        void standardize();

        // The following functions deal with the outside world.

        inline bool is_local() const;
        inline bool is_fully_qualified() const;
        void make_absolute();
        void make_absolute(const TFile &start_directory);

        bool make_canonical();

        TString to_os_specific() const;
        TString to_os_generic() const;

        bool exists() const;
        bool is_regular_file() const;
        bool is_directory() const;
        bool is_executable() const;
        int compare_timestamps(const TFile &other,
            bool this_missing_is_old = true,
            bool other_missing_is_old = true) const;
        bool resolve_filename(const TSearchPath &searchpath,
            const TString &default_extension = TString());
        bool make_relative_to(TFile directory, bool allow_backups = true);
        int find_on_searchpath(const TSearchPath &searchpath);

        bool scan_directory(vector_string &contents) const;

        bool open_read(std::ifstream &stream) const;
        bool open_write(std::ofstream &stream, bool truncate = true) const;
        bool open_append(std::ofstream &stream) const;
        bool open_read_write(std::fstream &stream) const;

        bool touch() const;

        bool unlink() const;
        bool rename_to(const TFile &other) const;

        bool make_dir() const;

        // Comparison operators are handy.
        inline bool operator == (const TString &other) const;
        inline bool operator != (const TString &other) const;
        inline bool operator < (const TString &other) const;

        inline void output(std::ostream &out) const;

    private:
        void locate_basename();
        void locate_extension();
        size_t get_common_prefix(const TString &other) const;
        static int count_slashes(const TString &str);
        bool r_make_canonical(const TFile &cwd);

        TString _filename;
        // We'll make these size_t instead of TString::size_type to help out
        // cppParser.
        size_t _dirname_end;
        size_t _basename_start;
        size_t _basename_end;
        size_t _extension_start;

        int _flags;

    };

    inline std::ostream &operator << (std::ostream &out, const TFile &n) {
        n.output(out);
        return out;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::Constructor
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    inline TFile::
        TFile(const TString &filename) {
            (*this) = filename;
            _flags = 0;
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile::TFile(const char *filename) 
    {
        (*this) = filename;
        _flags = 0;
    }


    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile::TFile(const TFile &copy)
        : _filename(copy._filename),
        _dirname_end(copy._dirname_end),
        _basename_start(copy._basename_start),
        _basename_end(copy._basename_end),
        _extension_start(copy._extension_start),
        _flags(copy._flags)
    {
    }

    //-----------------------------------------------------------------------
    //                       t e x t F i l e n a m e
    //-----------------------------------------------------------------------
    inline TFile TFile::text_filename(const TString &filename) 
    {
        TFile result(filename);
        result.set_text();
        return result;
    }

    //-----------------------------------------------------------------------
    //                     b i n a r y F i l e n a m e
    //-----------------------------------------------------------------------
    inline TFile TFile::binary_filename(const TString &filename) {
        TFile result(filename);
        result.set_binary();
        return result;
    }

    //-----------------------------------------------------------------------
    //                        d s o F i l e n a m e
    //-----------------------------------------------------------------------
    inline TFile TFile::dso_filename(const TString &filename) 
    {
        TFile result(filename);
        result.set_type(T_dso);
        return result;
    }

    //-----------------------------------------------------------------------
    //                  e x e c u t a b l e F i l e n a m e
    //-----------------------------------------------------------------------
    inline TFile TFile::executable_filename(const TString &filename) 
    {
        TFile result(filename);
        result.set_type(T_executable);
        return result;
    }

    //-----------------------------------------------------------------------
    //                            ~ T F i l e
    //-----------------------------------------------------------------------
    inline TFile::~TFile() 
    {
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile &TFile::operator = (const TString &filename) 
    {
        _filename = filename;

        locate_basename();
        locate_extension();
        return *this;
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile &TFile::operator = (const char *filename)
    {
        assert(filename != NULL);
        return (*this) = TString(filename);
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile &TFile::operator = (const TFile &copy) 
    {
        _filename = copy._filename;
        _dirname_end = copy._dirname_end;
        _basename_start = copy._basename_start;
        _basename_end = copy._basename_end;
        _extension_start = copy._extension_start;
        _flags = copy._flags;
        return *this;
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile::operator const TString & () const 
    {
        return _filename;
    }

    //-----------------------------------------------------------------------
    //                          c _ s t r 
    //-----------------------------------------------------------------------
    inline const char *TFile::c_str() const 
    {
        return _filename.c_str();
    }

    //-----------------------------------------------------------------------
    //                          e m p t y 
    //-----------------------------------------------------------------------
    inline bool TFile::empty() const 
    {
        return _filename.empty();
    }

    //-----------------------------------------------------------------------
    //                           l e n g t h 
    //-----------------------------------------------------------------------
    inline size_t TFile::length() const 
    {
        return _filename.length();
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline char TFile::operator [] (int n) const 
    {
        assert(n >= 0 && n < (int)_filename.length());
        return _filename[n];
    }


    //-----------------------------------------------------------------------
    //                          g e t F u l l P a t h
    //-----------------------------------------------------------------------
    inline TString TFile::get_fullpath() const 
    {
        return _filename;
    }

    //-----------------------------------------------------------------------
    //                          g e t D i r N a m e
    //-----------------------------------------------------------------------
    inline TString TFile::get_dirname() const 
    {
        return _filename.substr(0, _dirname_end);
    }

    //-----------------------------------------------------------------------
    //                          g e t B a s e N a m e
    //-----------------------------------------------------------------------
    inline TString TFile::get_basename() const 
    {
        return _filename.substr(_basename_start);
    }


    //-----------------------------------------------------------------------
    //                g e t F u l l P a t h W O E x t e n s i o n
    //-----------------------------------------------------------------------
    inline TString TFile::get_fullpath_wo_extension() const 
    {
        return _filename.substr(0, _basename_end);
    }


    //-----------------------------------------------------------------------
    //                g e t B a s e N a m e W O E x t e n s i o n 
    //-----------------------------------------------------------------------
    inline TString TFile::get_basename_wo_extension() const 
    {
        if (_basename_end == TString::npos) {
            return _filename.substr(_basename_start);
        } else {
            return _filename.substr(_basename_start, _basename_end - _basename_start);
        }
    }


    //-----------------------------------------------------------------------
    //                          g e t E x t e n s i o n
    //-----------------------------------------------------------------------
    inline TString TFile::get_extension() const 
    {
        if (_extension_start == TString::npos) 
        {
            return TString();
        } else 
        {
            return _filename.substr(_extension_start);
        }
    }

    //-----------------------------------------------------------------------
    //                          s e t B i n a r y
    //-----------------------------------------------------------------------
    inline void TFile::set_binary() 
    {
        _flags = (_flags & ~F_text) | F_binary;
    }

    //-----------------------------------------------------------------------
    //                           s e t T e x t 
    //-----------------------------------------------------------------------
    inline void TFile::set_text() 
    {
        _flags = (_flags & ~F_binary) | F_text;
    }

    //-----------------------------------------------------------------------
    //                           i s B i n a r y
    //-----------------------------------------------------------------------
    inline bool TFile::is_binary() const 
    {
        return ((_flags & F_binary) != 0);
    }

    //-----------------------------------------------------------------------
    //                             i s T e x t
    //-----------------------------------------------------------------------
    inline bool TFile::is_text() const 
    {
        return ((_flags & F_text) != 0);
    }

    //-----------------------------------------------------------------------
    //                          s e t T y p e
    //-----------------------------------------------------------------------
    inline void TFile::set_type(TFile::Type type) 
    {
        _flags = (_flags & ~F_type) | type;
        switch (type) 
        {
        case T_dso:
        case T_executable:
            set_binary();

        case T_general:
            break;
        }
    }

    //-----------------------------------------------------------------------
    //                          g e t T y p e
    //-----------------------------------------------------------------------
    inline TFile::Type TFile::get_type() const 
    {
        return (Type)(_flags & (int)F_type);
    }

    //-----------------------------------------------------------------------
    //                           i s L o c a l
    //-----------------------------------------------------------------------
    inline bool TFile::is_local() const 
    {
        return _filename.empty() || _filename[0] != '/';
    }

    //-----------------------------------------------------------------------
    //                       i s F u l l y Q u a l i f i e d
    //-----------------------------------------------------------------------
    inline bool TFile::is_fully_qualified() const 
    {
        return
            (_filename.size() > 2 && _filename[0] == '.' && _filename[1] == '/') ||
            (!_filename.empty() && _filename[0] == '/');
    }

    //-----------------------------------------------------------------------
    //                                = =
    //-----------------------------------------------------------------------
    inline bool TFile::operator == (const TString &other) const 
    {
        return (*(TString *)this) == other;
    }

    //-----------------------------------------------------------------------
    //                                ! =
    //-----------------------------------------------------------------------
    inline bool TFile::operator != (const TString &other) const 
    {
        return (*(TString *)this) != other;
    }

    //-----------------------------------------------------------------------
    //                                <
    //-----------------------------------------------------------------------
    inline bool TFile::operator < (const TString &other) const 
    {
        return (*(TString *)this) < other;
    }


    //-----------------------------------------------------------------------
    //                            o u t p u t
    //-----------------------------------------------------------------------
    inline void TFile::output(std::ostream &out) const 
    {
        out << _filename;
    }

    TString downcase(const TString &params);

}

#endif