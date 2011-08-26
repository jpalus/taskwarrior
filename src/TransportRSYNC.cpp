////////////////////////////////////////////////////////////////////////////////
// taskwarrior - a command line task list manager.
//
// Copyright 2010 - 2011, Johannes Schlatow.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the
//
//     Free Software Foundation, Inc.,
//     51 Franklin Street, Fifth Floor,
//     Boston, MA
//     02110-1301
//     USA
//
////////////////////////////////////////////////////////////////////////////////

#define L10N                                           // Localization complete.

#include <text.h>
#include <i18n.h>
#include <TransportRSYNC.h>

////////////////////////////////////////////////////////////////////////////////
TransportRSYNC::TransportRSYNC(const Uri& uri) : Transport(uri)
{
	_executable = "rsync";
}

////////////////////////////////////////////////////////////////////////////////
void TransportRSYNC::send(const std::string& source)
{
	if (_uri._host == "")
		throw std::string (STRING_TRANSPORT_RSYNC_URI);

	// Is there more than one file to transfer?
	// Then path has to end with a '/'
	if (is_filelist(source) && !_uri.is_directory())
    throw format (STRING_TRANSPORT_URI_NODIR, _uri._path);

	// cmd line is: rsync [--port=PORT] source [user@]host::path
	if (_uri._port != "")
	{
		_arguments.push_back ("--port=" + _uri._port);
	}

	_arguments.push_back (source);

	if (_uri._user != "")
	{
		_arguments.push_back (_uri._user + "@" + _uri._host + "::" + _uri._path);
	}
	else
	{
		_arguments.push_back (_uri._host + "::" + _uri._path);
	}

	if (execute())
    throw std::string (STRING_TRANSPORT_RSYNC_NORUN);
}

////////////////////////////////////////////////////////////////////////////////
void TransportRSYNC::recv(std::string target)
{
	if (_uri._host == "")
		throw std::string (STRING_TRANSPORT_RSYNC_URI);

	// Is there more than one file to transfer?
	// Then target has to end with a '/'
	if (is_filelist(_uri._path) && !is_directory(target))
    throw format (STRING_TRANSPORT_URI_NODIR, target);

	// cmd line is: rsync [--port=PORT] [user@]host::path target
	if (_uri._port != "")
		_arguments.push_back ("--port=" + _uri._port);

	if (_uri._user != "")
	{
		_arguments.push_back (_uri._user + "@" + _uri._host + "::" + _uri._path);
	}
	else
	{
		_arguments.push_back (_uri._host + "::" + _uri._path);
	}

	_arguments.push_back (target);

	if (execute())
    throw std::string (STRING_TRANSPORT_RSYNC_NORUN);
}

////////////////////////////////////////////////////////////////////////////////
