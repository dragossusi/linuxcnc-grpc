package ro.dragossusi.grpc.linuxcnc

import io.grpc.ManagedChannelBuilder
import ro.dragossusi.proto.linuxcnc.LinuxCncServiceGrpc
import ro.dragossusi.proto.linuxcnc.Linuxcnc
import ro.dragossusi.proto.linuxcnc.Linuxcnc.GetComponentsResponse
import java.util.concurrent.TimeUnit

fun main(args: Array<String>) {
    val channel = ManagedChannelBuilder.forTarget("localhost")
        .usePlaintext()
        .build()
    try {
        val service = LinuxCncServiceGrpc.newBlockingStub(channel)
        val components = service.getComponents(Linuxcnc.GetComponentsRequest.newBuilder().build())
        components.forEachRemaining { response: GetComponentsResponse ->
            val list = response.componentsList
            println(list)
        }
    } finally {
        channel.shutdownNow()
            .awaitTermination(5, TimeUnit.SECONDS)
    }
}