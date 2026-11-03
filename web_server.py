import uasyncio as asyncio
import config

movement_handler = None
light_handler = None

CHUNK_SIZE = 1024  # bytes per chunk to save RAM


def _content_type(path):
    if path.endswith(".html"):
        return "text/html"
    if path.endswith(".css"):
        return "text/css"
    if path.endswith(".png"):
        return "image/png"
    return "application/octet-stream"


async def _handle_client(reader, writer):
    try:
        request_line = await reader.readline()
        if not request_line:
            writer.close()
            return

        request_line = request_line.decode()
        parts = request_line.split()
        if len(parts) < 2:
            writer.close()
            return

        method = parts[0]
        path = parts[1]

        # Read remaining headers until empty line
        while True:
            header_line = await reader.readline()
            if not header_line or header_line == b"\r\n":
                break

        await _route(method, path, writer)

    except Exception:
        pass
    finally:
        try:
            writer.close()
        except Exception:
            pass


async def _send_file(writer, file_path, ctype):
    """Send a file in chunks to avoid loading it entirely into RAM."""
    try:
        with open(file_path, "rb") as f:
            # Get file size for Content-Length header
            f.seek(0, 2)  # seek to end
            file_size = f.tell()
            f.seek(0)  # back to start

            writer.write("HTTP/1.1 200 OK\r\n".encode())
            writer.write("Content-Type: {}\r\n".format(ctype).encode())
            writer.write("Content-Length: {}\r\n".format(file_size).encode())
            writer.write(b"Connection: close\r\n")
            writer.write(b"\r\n")

            while True:
                chunk = f.read(CHUNK_SIZE)
                if not chunk:
                    break
                writer.write(chunk)
                await writer.drain()
    except OSError:
        # File not found
        body = b"<h1>404 Not Found</h1><p>File not found.</p>"
        writer.write("HTTP/1.1 404 Not Found\r\n".encode())
        writer.write("Content-Type: text/html\r\n".encode())
        writer.write("Content-Length: {}\r\n".format(len(body)).encode())
        writer.write(b"Connection: close\r\n")
        writer.write(b"\r\n")
        writer.write(body)


async def _send_response(writer, status, ctype, body):
    writer.write("HTTP/1.1 {}\r\n".format(status).encode())
    writer.write("Content-Type: {}\r\n".format(ctype).encode())
    writer.write("Content-Length: {}\r\n".format(len(body)).encode())
    writer.write(b"Connection: close\r\n")
    writer.write(b"\r\n")
    writer.write(body)


async def _route(method, path, writer):
    # --- GET: static files ---
    if method == "GET":
        if path == "/":
            path = "/index.html"

        file_path = config.WEB_ROOT + path
        ctype = _content_type(file_path)
        await _send_file(writer, file_path, ctype)
        return

    # --- POST: movement and light ---
    if method == "POST":
        if path == "/movement/left":
            if movement_handler:
                movement_handler("left")
            await _send_response(writer, "204 No Content", "text/plain", b"")
            return
        elif path == "/movement/right":
            if movement_handler:
                movement_handler("right")
            await _send_response(writer, "204 No Content", "text/plain", b"")
            return
        elif path == "/movement/stop":
            if movement_handler:
                movement_handler("stop")
            await _send_response(writer, "204 No Content", "text/plain", b"")
            return
        elif path == "/light":
            if light_handler:
                light_handler()
            await _send_response(writer, "201 Created", "text/plain", b"")
            return

    body = b"<h1>404 Not Found</h1>"
    await _send_response(writer, "404 Not Found", "text/html", body)


async def start_server():
    srv = await asyncio.start_server(_handle_client, "0.0.0.0", config.PORT)
    print("Web server started on port", config.PORT)
    return srv
