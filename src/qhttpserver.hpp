/*
 * Copyright 2011-2014 Nikhil Marathe <nsm.nikhil@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef Q_HTTP_SERVER_HPP
#define Q_HTTP_SERVER_HPP

#define QHTTPSERVER_VERSION_MAJOR 1
#define QHTTPSERVER_VERSION_MINOR 0
#define QHTTPSERVER_VERSION_PATCH 0

///////////////////////////////////////////////////////////////////////////////
#include "qhttpserverapi.hpp"
#include "qhttpserverfwd.hpp"

#include <QTcpServer>
#include <QHostAddress>

///////////////////////////////////////////////////////////////////////////////

/** Maps status codes to string reason phrases. */
typedef QHash<int, QString> TStatusCodes;

///////////////////////////////////////////////////////////////////////////////

/** The QHttpServer class forms the basis of this project.
 * It is a fast, non-blocking HTTP server.
 *  These are the steps to create a server, handle and respond to requests:
 * <ol>
 *     <li>Create an instance of QHttpServer.</li>
 *     <li>Connect a slot to the newRequest() signal.</li>
 *     <li>Create a QCoreApplication to drive the server event loop.</li>
 *     <li>Respond to clients by writing out to the QHttpResponse object.</li>
 * </ol>
 */
class QHTTPSERVER_API QHttpServer : public QTcpServer
{
    Q_OBJECT

public:
    static const TStatusCodes& statusCodes();

public:
    /** construct a new HTTP Server. */
    QHttpServer(QObject *parent = 0);

    virtual     ~QHttpServer();

    /** starts the server on @c port listening on all interfaces. */
    bool        listen(const QHostAddress& address, quint16 port);

    bool        listen(quint16 port) {
        return listen(QHostAddress::Any, port);
    }

signals:
    /** emitted when a client makes a new request to the server.
     * The slot should use the given @c request and @c response
     *  objects to communicate with the client.
     * @param request New incoming request.
     * @param response Response object to the request. */
    void        newRequest(QHttpRequest *request, QHttpResponse *response);

//private slots:
//    void        newConnection();

protected:
    virtual void incomingConnection(qintptr handle);
};

///////////////////////////////////////////////////////////////////////////////
#endif // define Q_HTTP_SERVER_HPP
